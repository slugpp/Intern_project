/**
 * @file      utilities.h
 * @author    Lewis He (lewishe@outlook.com)
 * @license   MIT
 * @copyright Copyright (c) 2025  Shenzhen Xin Yuan Electronic Technology Co., Ltd
 * @date      2025-04-30
 * 
 */

#pragma once

// Note:

// When using ArduinoIDE, you must select a corresponding board type.
// If you don’t know which board type you have, please click on the link to view it.
// 使用ArduinoIDE ,必须选择一个对应的板型 ,如果你不知道你的板型是哪种，请点击链接进行查看

// The model name with S3 after it is the ESP32-S3 version, otherwise it is the ESP32 version
// 型号名称后面带S3的为ESP32-S3版本，否则是ESP32版本


// Products Link:https://www.lilygo.cc/products/t-sim-a7670e
 #define LILYGO_T_A7670

// Products Link: https://lilygo.cc/products/t-call-v1-4
// #define LILYGO_T_CALL_A7670_V1_0

// Products Link: https://lilygo.cc/products/t-sim-7670g-s3
// #define LILYGO_T_SIM7670G_S3

// Products Link: https://lilygo.cc/products/t-a7608e-h?variant=42860532433077
// #define LILYGO_T_A7608X

// Products Link: https://lilygo.cc/products/t-a7608e-h?variant=43932699033781
// #define LILYGO_T_A7608X_S3

// Products Link: ......
// #define LILYGO_A7670X_S3

// Products Link: https://lilygo.cc/products/t-sim7000g
// #define LILYGO_SIM7000G

// Products Link: https://lilygo.cc/products/a-t-pcie?variant=42335922094261
// #define LILYGO_T_PCIE_A767X

// Products Link: https://lilygo.cc/products/a-t-pcie?variant=42335921897653
// #define LILYGO_T_PCIE_SIM7000G

// Products Link: https://lilygo.cc/products/a-t-pcie?variant=42335921995957
// #define LILYGO_T_PCIE_SIM7080G

// Products Link: https://lilygo.cc/products/t-eth-elite-1?variant=44498205049013
// #define LILYGO_T_ETH_ELITE_A7670X


#if defined(LILYGO_T_A7670)

    #define MODEM_BAUDRATE                      (115200)
    #define MODEM_DTR_PIN                       (25)
    #define MODEM_TX_PIN                        (26)
    #define MODEM_RX_PIN                        (27)
    // The modem boot pin needs to follow the startup sequence.
    #define BOARD_PWRKEY_PIN                    (4)
    #define BOARD_BAT_ADC_PIN                       (35)
    // The modem power switch must be set to HIGH for the modem to supply power.
    #define BOARD_POWERON_PIN                   (12)
    #define MODEM_RING_PIN                      (33)
    #define MODEM_RESET_PIN                     (5)
    #define BOARD_MISO_PIN                      (2)
    #define BOARD_MOSI_PIN                      (15)
    #define BOARD_SCK_PIN                       (14)
    #define BOARD_SD_CS_PIN                     (13)
    #define BOARD_BAT_ADC_PIN                   (35)
    #define MODEM_RESET_LEVEL                   HIGH
    #define SerialAT                            Serial1

    #define MODEM_GPS_ENABLE_GPIO               (-1)
    #define MODEM_GPS_ENABLE_LEVEL              (-1)

    #ifndef TINY_GSM_MODEM_A7670
        #define TINY_GSM_MODEM_A7670
    #endif

    // It is only available in V1.4 version. In other versions, IO36 is not connected.
    #define BOARD_SOLAR_ADC_PIN                 (36)


#elif defined(LILYGO_T_CALL_A7670_V1_0)
    #define MODEM_BAUDRATE                      (115200)
    #define MODEM_DTR_PIN                       (14)
    #define MODEM_TX_PIN                        (26)
    #define MODEM_RX_PIN                        (25)
    // The modem boot pin needs to follow the startup sequence.
    #define BOARD_PWRKEY_PIN                    (4)
    #define BOARD_LED_PIN                       (12)
    // There is no modem power control, the LED Pin is used as a power indicator here.
    #define BOARD_POWERON_PIN                   (BOARD_LED_PIN)
    #define MODEM_RING_PIN                      (13)
    #define MODEM_RESET_PIN                     (27)
    #define MODEM_RESET_LEVEL                   LOW
    #define SerialAT                            Serial1


    #define MODEM_GPS_ENABLE_GPIO               (-1)
    #define MODEM_GPS_ENABLE_LEVEL              (-1)


    #ifndef TINY_GSM_MODEM_A7670
        #define TINY_GSM_MODEM_A7670
    #endif

#elif defined(LILYGO_T_CALL_A7670_V1_1)

    #define MODEM_BAUDRATE                      (115200)
    #define MODEM_DTR_PIN                       (32)
    #define MODEM_TX_PIN                        (27)
    #define MODEM_RX_PIN                        (26)
    // The modem boot pin needs to follow the startup sequence.
    #define BOARD_PWRKEY_PIN                    (4)
    #define BOARD_LED_PIN                       (13)
    // There is no modem power control, the LED Pin is used as a power indicator here.
    #define BOARD_POWERON_PIN                   (BOARD_LED_PIN)
    #define MODEM_RING_PIN                      (33)
    #define MODEM_RESET_PIN                     (5)
    #define MODEM_RESET_LEVEL                   LOW
    #define SerialAT                            Serial1

    #define MODEM_GPS_ENABLE_GPIO               (-1)
    #define MODEM_GPS_ENABLE_LEVEL              (-1)

    #ifndef TINY_GSM_MODEM_A7670
        #define TINY_GSM_MODEM_A7670
    #endif

#elif defined(LILYGO_T_SIM7670G_S3)
    #define MODEM_BAUDRATE                      (115200)
    #define MODEM_DTR_PIN                       (9)
    #define MODEM_TX_PIN                        (11)
    #define MODEM_RX_PIN                        (10)
    // The modem boot pin needs to follow the startup sequence.
    #define BOARD_PWRKEY_PIN                    (18)
    #define BOARD_LED_PIN                       (12)
    // There is no modem power control, the LED Pin is used as a power indicator here.
    #define BOARD_POWERON_PIN                   (BOARD_LED_PIN)
    #define MODEM_RING_PIN                      (3)
    #define MODEM_RESET_PIN                     (17)
    #define MODEM_RESET_LEVEL                   LOW
    #define SerialAT                            Serial1

    #define BOARD_BAT_ADC_PIN                   (4)
    #define BOARD_SOLAR_ADC_PIN                 (5)
    #define BOARD_MISO_PIN                      (47)
    #define BOARD_MOSI_PIN                      (14)
    #define BOARD_SCK_PIN                       (21)
    #define BOARD_SD_CS_PIN                     (13)

    #ifndef TINY_GSM_MODEM_SIM7672
        #define TINY_GSM_MODEM_SIM7672
    #endif

    #define MODEM_GPS_ENABLE_GPIO               (4)
    #define MODEM_GPS_ENABLE_LEVEL              (1)


#elif defined(LILYGO_T_A7608X)

    #define MODEM_BAUDRATE                      (115200)
    #define MODEM_DTR_PIN                       (25)
    #define MODEM_TX_PIN                        (26)
    #define MODEM_RX_PIN                        (27)
    // The modem boot pin needs to follow the startup sequence.
    #define BOARD_PWRKEY_PIN                    (4)
    #define BOARD_BAT_ADC_PIN                   (35)
    // The modem power switch must be set to HIGH for the modem to supply power.
    #define BOARD_POWERON_PIN                   (12)        //T-A7608-V2 is onboard led
    #define MODEM_RING_PIN                      (33)
    #define MODEM_RESET_PIN                     (5)         //T-A7608-V2 no connection
    #define BOARD_MISO_PIN                      (2)
    #define BOARD_MOSI_PIN                      (15)
    #define BOARD_SCK_PIN                       (14)
    #define BOARD_SD_CS_PIN                     (13)

    #define MODEM_RESET_LEVEL                   HIGH
    #define SerialAT                            Serial1


    #ifndef TINY_GSM_MODEM_A7608
        #define TINY_GSM_MODEM_A7608
    #endif

    // only version v1.1 or V2  has solar adc pin
    #define BOARD_SOLAR_ADC_PIN                 (34)


    // 127 is defined in GSM as the AUXVDD index
    #define MODEM_GPS_ENABLE_GPIO               (127)
    #define MODEM_GPS_ENABLE_LEVEL              (1)

#elif defined(LILYGO_T_A7608X_S3)

    #define MODEM_BAUDRATE                      (115200)
    #define MODEM_DTR_PIN                       (7)
    #define MODEM_TX_PIN                        (17)
    #define MODEM_RX_PIN                        (18)
    // The modem boot pin needs to follow the startup sequence.
    #define BOARD_PWRKEY_PIN                    (15)
    #define BOARD_BAT_ADC_PIN                   (4)
    // The modem power switch must be set to HIGH for the modem to supply power.
    // #define BOARD_POWERON_PIN                   (12)
    #define MODEM_RING_PIN                      (6)
    #define MODEM_RESET_PIN                     (16)
    #define BOARD_MISO_PIN                      (47)
    #define BOARD_MOSI_PIN                      (14)
    #define BOARD_SCK_PIN                       (21)
    #define BOARD_SD_CS_PIN                     (13)

    #define MODEM_RESET_LEVEL                   LOW
    #define SerialAT                            Serial1

    #ifndef TINY_GSM_MODEM_A7608
        #define TINY_GSM_MODEM_A7608
    #endif

    // only version v1.1 has solar adc pin
    #define BOARD_SOLAR_ADC_PIN                 (3)

    // 127 is defined in GSM as the AUXVDD index
    #define MODEM_GPS_ENABLE_GPIO               (127)
    #define MODEM_GPS_ENABLE_LEVEL              (1)

#elif defined(LILYGO_T_A7608X_DC_S3)

    #define MODEM_DTR_PIN                       (5)
    #define MODEM_RX_PIN                        (42)
    #define MODEM_TX_PIN                        (41)
    // The modem boot pin needs to follow the startup sequence.
    #define BOARD_PWRKEY_PIN                    (38)
    #define MODEM_RING_PIN                      (6)
    #define MODEM_RESET_PIN                     (40)
    #define MODEM_RTS_PIN                       (1)
    #define MODEM_CTS_PIN                       (2)

    #define MODEM_RESET_LEVEL                   LOW
    #define SerialAT                            Serial1

    #ifndef TINY_GSM_MODEM_A7608
        #define TINY_GSM_MODEM_A7608
    #endif

    // 127 is defined in GSM as the AUXVDD index
    #define MODEM_GPS_ENABLE_GPIO               (127)
    #define MODEM_GPS_ENABLE_LEVEL              (1)


#elif defined(LILYGO_SIM7000G)

    #define MODEM_DTR_PIN                       (25)
    #define MODEM_RX_PIN                        (26)
    #define MODEM_TX_PIN                        (27)

    // The modem boot pin needs to follow the startup sequence.
    #define BOARD_PWRKEY_PIN                    (4)
    #define MODEM_RING_PIN                      (33)
    #define BOARD_LED_PIN                       (12)
    #define LED_ON                              (LOW)

    #define SerialAT                            Serial1

    #ifndef TINY_GSM_MODEM_SIM7000SSL
        #define TINY_GSM_MODEM_SIM7000SSL
    #endif

    // 127 is defined in GSM as the AUXVDD index
    #define MODEM_GPS_ENABLE_GPIO               (4)
    #define MODEM_GPS_ENABLE_LEVEL              (0)


#elif defined(LILYGO_A7670X_S3)


    #define BOARD_SDA_PIN                       (3)
    #define BOARD_SCL_PIN                       (2)

    #define MODEM_BAUDRATE                      (115200)
    #define MODEM_DTR_PIN                       (7)
    #define MODEM_TX_PIN                        (4)
    #define MODEM_RX_PIN                        (5)
    #define MODEM_RING_PIN                      (6)

    #define MODEM_GPS_RX_PIN                    (15)
    #define MODEM_GPS_TX_PIN                    (16)
    #define MODEM_GPS_PPS_PIN                   (17)

    // The modem boot pin needs to follow the startup sequence.
    #define BOARD_PWRKEY_PIN                    (46)

    #define BOARD_BAT_ADC_PIN                       (8)
    #define BOARD_SOLAR_ADC_PIN                 (18)

    #define BOARD_MISO_PIN                      (13)
    #define BOARD_MOSI_PIN                      (11)
    #define BOARD_SCK_PIN                       (12)
    #define BOARD_SD_CS_PIN                     (10)

    #define CAMERA_PWDN_PIN                     (-1)
    #define CAMERA_RESET_PIN                    (-1)
    #define CAMERA_XCLK_PIN                     (36)
    #define CAMERA_SIOD_PIN                     (40)
    #define CAMERA_SIOC_PIN                     (1)
    #define CAMERA_VSYNC_PIN                    (42)
    #define CAMERA_HREF_PIN                     (9)
    #define CAMERA_PCLK_PIN                     (41)
    #define CAMERA_Y9_PIN                       (45)
    #define CAMERA_Y8_PIN                       (39)
    #define CAMERA_Y7_PIN                       (38)
    #define CAMERA_Y6_PIN                       (7)
    #define CAMERA_Y5_PIN                       (35)
    #define CAMERA_Y4_PIN                       (48)
    #define CAMERA_Y3_PIN                       (47)
    #define CAMERA_Y2_PIN                       (14)

    #define BOARD_LED_PIN                       (37)
    #define LED_ON                              (HIGH)

    #define SerialAT                            Serial1

    #define MODEM_GPS_ENABLE_GPIO               (1)
    #define MODEM_GPS_ENABLE_LEVEL              (1)

    #ifndef TINY_GSM_MODEM_A7670
        #define TINY_GSM_MODEM_A7670
    #endif

#elif defined(LILYGO_T_PCIE_A767X)

    #define MODEM_DTR_PIN                       (32)
    #define MODEM_RX_PIN                        (26)
    #define MODEM_TX_PIN                        (27)
    // The modem power switch must be set to HIGH for the modem to supply power.
    #define BOARD_POWERON_PIN                   (25)
    // The modem boot pin needs to follow the startup sequence.
    #define BOARD_PWRKEY_PIN                    (4)
    #define MODEM_RING_PIN                      (33)
    #define BOARD_LED_PIN                       (12)
    #define PMU_IRQ                             (35)

    // No connect to reset pin to modem ,set dummy reset pin
    #define MODEM_RESET_PIN                     (BOARD_LED_PIN)
    #define MODEM_RESET_LEVEL                   (0)

    #define SerialAT                            Serial1

    #ifndef TINY_GSM_MODEM_A7670
        #define TINY_GSM_MODEM_A7670
    #endif

    // 127 is defined in GSM as the AUXVDD index
    #define MODEM_GPS_ENABLE_GPIO               (4)
    #define MODEM_GPS_ENABLE_LEVEL              (0)

#elif defined(LILYGO_T_PCIE_SIM7000G)

    #define LILYGO_T_PCIE

    #ifndef TINY_GSM_MODEM_SIM7000SSL
        #define TINY_GSM_MODEM_SIM7000SSL
    #endif

#elif defined(LILYGO_T_PCIE_SIM7080G)

    #define LILYGO_T_PCIE

    #ifndef TINY_GSM_MODEM_SIM7080
        #define TINY_GSM_MODEM_SIM7080
    #endif

#elif defined(LILYGO_T_ETH_ELITE_A7670X)

    #define LILYGO_T_ETH_ELITE

    #ifndef TINY_GSM_MODEM_A7670
        #define TINY_GSM_MODEM_A7670
    #endif

#else
    #error "Use ArduinoIDE, please open the macro definition corresponding to the board above <utilities.h>"
#endif


#ifdef LILYGO_T_PCIE

    #define MODEM_DTR_PIN           (32)
    #define MODEM_RX_PIN            (26)
    #define MODEM_TX_PIN            (27)
    // The modem power switch must be set to HIGH for the modem to supply power.
    #define BOARD_POWERON_PIN       (25)
    // The modem boot pin needs to follow the startup sequence.
    #define BOARD_PWRKEY_PIN        (4)
    #define MODEM_RING_PIN          (33)
    #define BOARD_LED_PIN           (12)
    #define PMU_IRQ                 (35)

    #define LED_ON                  (LOW)

    #define SerialAT                Serial1
#endif

#ifdef LILYGO_T_ETH_ELITE

    #define ETH_MISO_PIN             (47)
    #define ETH_MOSI_PIN             (21)
    #define ETH_SCLK_PIN             (48)
    #define ETH_CS_PIN               (45)
    #define ETH_INT_PIN              (14)
    #define ETH_RST_PIN              (-1)
    #define ETH_ADDR                 (1)

    #define SPI_MISO_PIN             (9)
    #define SPI_MOSI_PIN             (11)
    #define SPI_SCLK_PIN             (10)

    #define SD_MISO_PIN              (SPI_MISO_PIN)
    #define SD_MOSI_PIN              (SPI_MOSI_PIN)
    #define SD_SCLK_PIN              (SPI_SCLK_PIN)
    #define SD_CS_PIN                (12)

    #define BOARD_SDA_PIN             (17)
    #define BOARD_SCL_PIN             (18)

    #define ADC_BUTTONS_PIN           (7)
    #define MODEM_RX_PIN              (4)
    #define MODEM_TX_PIN              (6)
    #define MODEM_DTR_PIN             (5)
    #define MODEM_RING_PIN            (1)
    #define BOARD_PWRKEY_PIN          (3)

    #define GPS_RX_PIN                (39)
    #define GPS_TX_PIN                (42)

    #define BOARD_LED_PIN             (38)
    #define LED_ON                    (HIGH)

#endif

// T-Call-A767X V1.0 and V1.1 have different Pinmaps and cannot be used universally , Invalid version
// #define LILYGO_T_CALL_A7670_V1_1
// #define LILYGO_T_A7608X_DC_S3

