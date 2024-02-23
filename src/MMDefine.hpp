/*
 * @File :  MMDefine.hpp
 * @Time :  2024/02/13 10:35:10
 * @Vers :  1.0
 * @Desc :  相关定义
 */
#ifndef _MMDEF_HPP
#define _MMDEF_HPP

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#include <pins_arduino.h>

#include "MMFunc/MMFuncPool.hpp"

#define MMDEBUG // 定义调试宏用于控制调试输出

#define C_RP2040 // 定义使用的芯片类型

#ifdef C_RP2040
#define PIN_M (1u) // 定义矩阵屏幕引脚
#define PIN_IRR (0u) // 定义红外线接收引脚

#define PIN_I2C_DAT PIN_WIRE_SDA // I2C数据引脚, 4
#define PIN_I2C_CLK PIN_WIRE_SCL // I2C时钟引脚, 5

#define PIN_DS1302_CS (6u) // DS1302选择引脚

#define PIN_DHT (21u) // 定义DHT温湿度传感器引脚

#define PIN_LED_BUILTIN LED_BUILTIN // 板载LED引脚, 25

#define PIN_BUZZER (20u) // 蜂鸣器引脚

#define PIN_PIRR (7u) // 人体红外传感器引脚

// 定义SD访问相关的引脚
#ifndef ARDUINO_ARCH_RP2040
#error For RP2040 only
#endif

// SS = 17
// SCK = 18
// MOSI = 19
// MISO = 16

#if defined(ARDUINO_ARCH_MBED)

#define PIN_SD_MOSI PIN_SPI_MOSI
#define PIN_SD_MISO PIN_SPI_MISO
#define PIN_SD_SCK PIN_SPI_SCK
#define PIN_SD_SS PIN_SPI_SS

#else

#define PIN_SD_MOSI PIN_SPI0_MOSI
#define PIN_SD_MISO PIN_SPI0_MISO
#define PIN_SD_SCK PIN_SPI0_SCK
#define PIN_SD_SS PIN_SPI0_SS

#endif

#include <RP2040_SD.h>
#include <SPI.h>

#endif

// #define M_8x8

#ifdef M_8x8
#define M_HEIGHT (8) // 定义矩阵屏幕行数
#define M_WIDTH (8) // 定义矩阵屏幕列数
// 定义RGB矩阵
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(M_WIDTH, M_ROW, PIN_M,
    NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
    NEO_GRB + NEO_KHZ800);
#else
#define M_HEIGHT (16) // 定义矩阵屏幕行数
#define M_WIDTH (16) // 定义矩阵屏幕列数
// 定义矩阵屏幕类型
#define M_MATRIXTYPE (NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG)
// 定义LED类型
#define M_LEDTYPE (NEO_GRB + NEO_KHZ800)

#endif

#define M_PIXS (M_HEIGHT * M_WIDTH) // 定义矩阵像素数
#define M_BRIGHT (30) // 屏幕亮度0~255

// 定义红外遥控器的按键
#define IRK_NONE (0)

#define IRK_CH_MINUS (69)
#define IRK_CH (70)
#define IRK_CH_PLUS (71)

#define IRK_PRE (68)
#define IRK_NXT (64)
#define IRK_PAUSE (67)

#define IRK_MINUS (7)
#define IRK_PLUS (21)
#define IRK_EQ (9)

#define IRK_0 (22)
#define IRK_100 (25)
#define IRK_200 (13)

#define IRK_1 (12)
#define IRK_2 (24)
#define IRK_3 (94)

#define IRK_4 (8)
#define IRK_5 (28)
#define IRK_6 (90)

#define IRK_7 (66)
#define IRK_8 (82)
#define IRK_9 (74)

// RGB颜色的结构体
struct RGB {
    uint8_t R;
    uint8_t G;
    uint8_t B;
    static uint32_t Color(uint8_t r, uint8_t g, uint8_t b)
    { // 返回由RGB组成的颜色
        return ((uint16_t)(r & 0xF8) << 8) | ((uint16_t)(g & 0xFC) << 3) | (b >> 3);
    }
    uint32_t Color() {
        return Color(R, G, B);
    }
};

// // 定义功能池
// MMFuncPool FPool;

#endif