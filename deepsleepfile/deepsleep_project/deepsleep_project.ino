
#define TINY_GSM_RX_BUFFER 2048
#include <Wire.h>
#include <utilities.h>
#include <TinyGsmClient.h>
#include <ModbusMaster.h>
#include <RTClib.h>
#include <esp_sleep.h>

// ==== กำหนดขาและค่าคงที่ ====
#define MAX485_RE_DE_PIN 23
#define RS485_RX_PIN 34  // RO Pin
#define RS485_TX_PIN 32  // DI Pin
#define WAKEUP_PIN 33
#define APN "internet.true"
#define USER ""
#define PASS ""
#define BAUDRATE 115200

const char* host = "script.google.com";
const char* urlPath = "/macros/s/AKfycbzqZGl9whJprZGln1JDZuR-sXtf2tvhcTwRe3J1KutA9z6r1AlJpZFsY0jtd5zxrCA/exec";

// ==== โมดูลต่าง ๆ ====
HardwareSerial modemSerial(1);
TinyGsm modem(modemSerial);
ModbusMaster node;
RTC_DS3231 rtc;

// ==== เวลาที่จะส่งข้อมูล ====
struct TriggerTime {
  int hour;
  int minute;
};
TriggerTime triggerTimes[] = { { 8, 0 }, { 11, 0 }, { 14, 0 }, { 17, 0 } };
const int numTriggers = 4;

// ==== Modbus RS485 ====
void preTransmission() {
  digitalWrite(MAX485_RE_DE_PIN, HIGH);
  delay(2);
}
void postTransmission() {
  delay(2);
  digitalWrite(MAX485_RE_DE_PIN, LOW);
}

// ==== Alarm สำหรับ DS3231 ====
void setNextAlarm() {
  DateTime now = rtc.now();
  Serial.printf("[LOG] Current RTC time: %04d-%02d-%02d %02d:%02d:%02d\n",
                now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());

  // ล้าง alarm เดิมเพื่อป้องกันการขัดจังหวะซ้ำ
  rtc.clearAlarm(1);
  rtc.disableAlarm(1);

  for (int i = 0; i < numTriggers; i++) {
    int th = triggerTimes[i].hour;
    int tm = triggerTimes[i].minute;
    if (now.hour() < th || (now.hour() == th && now.minute() < tm)) {
      rtc.setAlarm1(DateTime(now.year(), now.month(), now.day(), th, tm, 0), DS3231_A1_Hour);
      rtc.writeSqwPinMode(DS3231_OFF);
      Serial.printf("[LOG] Alarm set for today at %02d:%02d\n", th, tm);
      return;
    }
  }

  // หากเลยเวลาทั้งหมดในวันนี้ ตั้ง alarm สำหรับวันถัดไป
  DateTime tomorrow = now + TimeSpan(1, 0, 0, 0);
  rtc.setAlarm1(DateTime(tomorrow.year(), tomorrow.month(), tomorrow.day(), triggerTimes[0].hour, triggerTimes[0].minute, 0), DS3231_A1_Hour);
  rtc.writeSqwPinMode(DS3231_OFF);
  Serial.printf("[LOG] Alarm set for tomorrow at %02d:%02d\n", triggerTimes[0].hour, triggerTimes[0].minute);
}

// ==== โมเด็ม ====
void powerOnModem() {
  pinMode(BOARD_PWRKEY_PIN, OUTPUT);
  digitalWrite(BOARD_PWRKEY_PIN, LOW);
  delay(100);
  digitalWrite(BOARD_PWRKEY_PIN, HIGH);
  delay(100);
  digitalWrite(BOARD_PWRKEY_PIN, LOW);
  delay(10000);  // หน่วงเวลา 10 วินาทีเพื่อให้โมเด็มสตาร์ท
  Serial.println("[LOG] Modem powered on");
}

bool sendATCommand(String cmd, String expected, unsigned long timeout) {
  modemSerial.println(cmd);
  unsigned long start = millis();
  String response = "";
  while (millis() - start < timeout) {
    while (modemSerial.available()) {
      response += (char)modemSerial.read();
    }
    if (response.indexOf(expected) != -1) {
      Serial.println("[LOG] " + cmd + ": " + response);
      return true;
    }
    if (response.indexOf("ERROR") != -1) {
      Serial.println("[ERROR] " + cmd + ": " + response);
      return false;
    }
    delay(100);
  }
  Serial.println("[ERROR] " + cmd + ": Timeout, response: " + response);
  return false;
}

bool configureModem() {
  if (!sendATCommand("AT+CPIN?", "READY", 3000)) {
    Serial.println("[ERROR] SIM card not ready");
    return false;
  }
  if (!sendATCommand("AT+CFUN=1", "OK", 3000)) {
    Serial.println("[ERROR] Failed to enable modem functionality");
    return false;
  }
  if (!sendATCommand("AT+COPS=0", "OK", 10000)) {
    Serial.println("[ERROR] Failed to set operator selection");
    return false;
  }
  if (!sendATCommand("AT+CTZU=1", "OK", 3000)) {
    Serial.println("[ERROR] Failed to enable time zone update");
    return false;
  }
  Serial.println("[LOG] Modem configured successfully");
  return true;
}

bool checkNetworkRegistration() {
  int retries = 60;
  for (int i = 0; i < retries; i++) {
    if (sendATCommand("AT+CSQ", "+CSQ: ", 3000)) {
      String response = "";
      while (modemSerial.available()) response += (char)modemSerial.read();
      Serial.println("[LOG] Signal strength: " + response);
      if (response.indexOf("99,99") == -1) {
        if (sendATCommand("AT+CREG?", "0,1", 3000) || sendATCommand("AT+CREG?", "0,5", 3000)) {
          Serial.println("[LOG] Network registered successfully");
          return true;
        }
      }
    }
    delay(3000);
  }
  Serial.println("[ERROR] Network registration failed");
  return false;
}

bool ensurePDPContext() {
  if (!sendATCommand("AT+CGDCONT=1,\"IP\",\"" + String(APN) + "\"", "OK", 3000)) {
    Serial.println("[ERROR] Failed to set PDP context");
    return false;
  }
  if (!sendATCommand("AT+CGACT=1,1", "OK", 3000)) {
    Serial.println("[ERROR] Failed to activate PDP context");
    return false;
  }
  Serial.println("[LOG] PDP context set successfully");
  return true;
}

bool syncRTCWithNetwork() {
  if (!sendATCommand("AT+CCLK?", "+CCLK: ", 3000)) {
    Serial.println("[ERROR] Failed to get network time");
    return false;
  }
  String response = "";
  while (modemSerial.available()) response += (char)modemSerial.read();
  int index = response.indexOf("+CCLK: ");
  if (index != -1) {
    String timeStr = response.substring(index + 8, index + 25);
    int year = 2000 + timeStr.substring(0, 2).toInt();
    int month = timeStr.substring(3, 5).toInt();
    int day = timeStr.substring(6, 8).toInt();
    int hour = timeStr.substring(9, 11).toInt();
    int minute = timeStr.substring(12, 14).toInt();
    int second = timeStr.substring(15, 17).toInt();
    rtc.adjust(DateTime(year, month, day, hour, minute, second));
    Serial.println("[LOG] RTC synchronized with network time");
    return true;
  }
  Serial.println("[ERROR] Failed to parse network time");
  return false;
}

float readWaterLevel() {
  uint16_t ctrl = (1 << 2) | (1 << 3);
  node.writeSingleRegister(0x08, ctrl);
  delay(1000);
  uint8_t result = node.readHoldingRegisters(0x05, 1);
  if (result == node.ku8MBSuccess) {
    float distance_cm = node.getResponseBuffer(0) / 100.0;
    float level = 100.0 - distance_cm;
    Serial.printf("[LOG] Water level: %.1f cm\n", level);
    return round(level * 10.0) / 10.0;
  } else {
    Serial.println("[ERROR] Failed to read water level");
    return -1;
  }
}

void SendData(float waterlevel, int hour, int minute) {
  if (!checkNetworkRegistration() || !ensurePDPContext()) {
    Serial.println("[ERROR] Cannot send data: Network or PDP context failure");
    return;
  }
  if (!sendATCommand("AT+HTTPINIT", "OK", 3000)) {
    Serial.println("[ERROR] Failed to initialize HTTP");
    return;
  }
  String url = "https://" + String(host) + String(urlPath);
  if (!sendATCommand("AT+HTTPPARA=\"URL\",\"" + url + "\"", "OK", 3000)) {
    Serial.println("[ERROR] Failed to set HTTP URL");
    return;
  }
  if (!sendATCommand("AT+HTTPPARA=\"CONTENT\",\"application/json\"", "OK", 3000)) {
    Serial.println("[ERROR] Failed to set HTTP content type");
    return;
  }
  char timeStr[6];
  sprintf(timeStr, "%02d:%02d", hour, minute);
  String jsonData = "{\"id\":\"esp001\",\"waterlevel\":" + String(waterlevel, 1) + ",\"time\":\"" + String(timeStr) + "\"}";
  if (!sendATCommand("AT+HTTPDATA=" + String(jsonData.length()) + ",10000", "DOWNLOAD", 3000)) {
    Serial.println("[ERROR] Failed to prepare HTTP data");
    return;
  }
  modemSerial.println(jsonData);
  delay(5000);
  if (!sendATCommand("AT+HTTPACTION=1", "OK", 5000)) {
    Serial.println("[ERROR] Failed to send HTTP request");
    return;
  }
  if (!sendATCommand("AT+HTTPTERM", "OK", 3000)) {
    Serial.println("[ERROR] Failed to terminate HTTP");
    return;
  }
  Serial.println("[LOG] Data sent successfully");
}

void setup() {
  Serial.begin(115200);
  delay(100);  // รอให้ Serial พร้อม
  Serial.println("[LOG] System started");

  // ตรวจสอบสาเหตุการตื่นจาก deep sleep
  esp_sleep_wakeup_cause_t wakeup_reason = esp_sleep_get_wakeup_cause();
  if (wakeup_reason == ESP_SLEEP_WAKEUP_EXT0) {
    Serial.println("[LOG] Woke up from deep sleep due to EXT0 (RTC interrupt)");
  } else {
    Serial.printf("[LOG] Woke up from deep sleep, reason: %d\n", wakeup_reason);
  }
  // ตรวจสอบสถานะ WAKEUP_PIN
  Serial.printf("[LOG] WAKEUP_PIN (GPIO %d) state: %d\n", WAKEUP_PIN, digitalRead(WAKEUP_PIN));

  Wire.begin();
  pinMode(MAX485_RE_DE_PIN, OUTPUT);
  digitalWrite(MAX485_RE_DE_PIN, LOW);
  pinMode(BOARD_PWRKEY_PIN, OUTPUT);
  pinMode(WAKEUP_PIN, INPUT_PULLUP);
  esp_sleep_enable_ext0_wakeup(GPIO_NUM_33, 0);

  if (!rtc.begin()) {
    Serial.println("[ERROR] RTC initialization failed");
    Serial.println("[LOG] Entering deep sleep due to RTC failure");
    esp_deep_sleep_start();
  }
  if (rtc.lostPower()) {
    Serial.println("[LOG] RTC lost power, setting default time");
    rtc.adjust(DateTime(2025, 5, 21, 0, 0, 0));
  }

  modemSerial.begin(BAUDRATE, SERIAL_8N1, MODEM_RX_PIN, MODEM_TX_PIN);
  Serial2.begin(115200, SERIAL_8N1, RS485_RX_PIN, RS485_TX_PIN);
  node.begin(0x0C, Serial2);
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);

  powerOnModem();
  int retry = 0;
  while (!modem.testAT(1000)) {
    Serial.println("[ERROR] Modem not responding, retrying...");
    if (retry++ > 15) {
      Serial.println("[ERROR] Modem failed to respond after retries");
      break;
    }
    powerOnModem();
  }
  if (modem.testAT(1000)) {
    Serial.println("[LOG] Modem responded to AT command");
    if (!configureModem()) {
      Serial.println("[ERROR] Modem configuration failed");
    } else if (!checkNetworkRegistration()) {
      Serial.println("[ERROR] Network registration failed");
    } else if (!ensurePDPContext()) {
      Serial.println("[ERROR] PDP context setup failed");
    } else if (!syncRTCWithNetwork()) {
      Serial.println("[ERROR] RTC sync failed, proceeding with current time");
    }
  }

  DateTime now = rtc.now();
  int hour = now.hour();
  int minute = now.minute();
  Serial.printf("[LOG] Current time: %04d-%02d-%02d %02d:%02d:%02d\n",
                now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());

  bool triggerMatched = false;
  for (int i = 0; i < numTriggers; i++) {
    if (hour == triggerTimes[i].hour && minute == triggerTimes[i].minute) {
      triggerMatched = true;
      float level = readWaterLevel();
      if (level >= 0 && modem.testAT(1000)) {
        SendData(level, hour, minute);
      } else {
        Serial.println("[ERROR] Skipping data send due to modem or water level error");
      }
      break;
    }
  }
  if (!triggerMatched) {
    Serial.println("[LOG] No trigger time matched, proceeding to set next alarm");
  }

  setNextAlarm();
  Serial.println("[LOG] Entering deep sleep now");
  delay(100);  // รอให้ Serial ล็อกข้อความเสร็จ
  esp_deep_sleep_start();
}

void loop() {}