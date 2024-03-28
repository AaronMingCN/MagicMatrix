/**
 * @file MMDefine.hpp
 * @date 2024/02/13 10:35:10
 * @author Aaron Ming
 * @version 1.0
 * @brief 系统相关定义
 * @details
 */

#ifndef _MMDEFINE_HPP
#define _MMDEFINE_HPP

#include <pins_arduino.h>

#include "MMFunc/MMFuncPool.hpp"

#define MMDEBUG // 定义调试宏用于控制调试输出

#define C_RP2040 // 定义使用的芯片类型

#ifdef C_RP2040

#define PIN_S1_TX SERIAL1_TX ///< 定义蓝牙使用串行数据引脚 PIN_SERIAL_TX (0ul) 系统默认
#define PIN_S1_RX SERIAL1_RX ///< 定义蓝牙使用串行数据引脚 PIN_SERIAL_RX (1ul)

#define PIN_IRR (2u) ///< 定义红外线接收引脚
#define PIN_M (3u) ///< 定义矩阵屏幕引脚

#define PIN_I2C_DAT PIN_WIRE_SDA ///< I2C数据引脚, 4
#define PIN_I2C_CLK PIN_WIRE_SCL ///< I2C时钟引脚, 5

#define PIN_DS1302_CS (6u) ///< DS1302选择引脚

#define PIN_DHT (21u) ///< 定义DHT温湿度传感器引脚

#define PIN_LED_BUILTIN LED_BUILTIN ///< 板载LED引脚, 25

#define PIN_BUZZER (20u) ///< 蜂鸣器引脚

#define PIN_PIRR (22u) ///< 人体红外传感器引脚

/// @brief 定义SD访问相关的引脚
#ifndef ARDUINO_ARCH_RP2040
#error For RP2040 only
#endif

#if defined(ARDUINO_ARCH_MBED)

#define PIN_SD_MOSI PIN_SPI_MOSI ///< SD引脚 MOSI = 19
#define PIN_SD_MISO PIN_SPI_MISO ///< SD引脚 MISO = 16
#define PIN_SD_SCK PIN_SPI_SCK ///< SD引脚 SCK = 18
#define PIN_SD_SS PIN_SPI_SS ///< SD引脚 SS = 17

#else

#define PIN_SD_MOSI PIN_SPI0_MOSI
#define PIN_SD_MISO PIN_SPI0_MISO
#define PIN_SD_SCK PIN_SPI0_SCK
#define PIN_SD_SS PIN_SPI0_SS

#endif

#include <RP2040_SD.h>
#include <SPI.h>

#endif

#define M_HEIGHT (16) ///< 定义矩阵屏幕行数
#define M_WIDTH (16) ///< 定义矩阵屏幕列数
/// 定义矩阵屏幕类型
#define M_MATRIXTYPE (NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG)
/// 定义LED类型
#define M_LEDTYPE (NEO_GRB + NEO_KHZ800)

#define M_PIXS (M_HEIGHT * M_WIDTH) ///< 定义矩阵像素数
#define M_BRIGHT (20) ///< 屏幕亮度0~255
#define M_BIRGHT_STANDBY (1u) ///< 工作亮度
#define M_PIRR_DELAY (20000u) ///< 人体检测延迟，毫秒

// 定义红外遥控器的按键

#define IRK_NONE (0) ///< 空

#define IRK_CH_MINUS (69) ///< CH+
#define IRK_CH (70) ///< CH
#define IRK_CH_PLUS (71) ///< CH-

#define IRK_PRE (68) ///< 上一曲
#define IRK_NXT (64) ///< 下一曲
#define IRK_PAUSE (67) ///< 暂停

#define IRK_MINUS (7) ///< Minus
#define IRK_PLUS (21) ///< Plus
#define IRK_EQ (9) ///< EQ

#define IRK_0 (22) ///< 0
#define IRK_100 (25) ///< 100
#define IRK_200 (13) ///< 200

#define IRK_1 (12) ///< 1
#define IRK_2 (24) ///< 2
#define IRK_3 (94) ///< 3

#define IRK_4 (8) ///< 4
#define IRK_5 (28) ///< 5
#define IRK_6 (90) ///< 6

#define IRK_7 (66) ///< 7
#define IRK_8 (82) ///< 8
#define IRK_9 (74) ///< 9



// 定义另一种标注红外遥控器的按键 

#define IRK_A IRK_CH_MINUS ///< A
#define IRK_B IRK_CH ///< B
#define IRK_C IRK_CH_PLUS ///< C

#define IRK_D IRK_PRE ///< D
#define IRK_UP IRK_NXT ///< Up
#define IRK_E IRK_PAUSE ///< E

#define IRK_LEFT IRK_MINUS ///< Left
#define IRK_SET IRK_PLUS ///< Set
#define IRK_RIGHT IRK_EQ ///< Right

#define IRK_DOWN IRK_100 ///< Down
#define IRK_F IRK_200 ///< F


/// @brief 配置文件名称
/// @note 保存的格式位JSON格式，由于FAT文件系统不支持4个字符的扩展名，所以这里用js
#define FILENAME_CFG "MMCFG.js"
#define FILENAME_LOGO "LOGO.bmp" ///< 定义LOGO在SD卡中的文件名

#define CFG_MENUCATE "CurrMenuCate" ///< 配置文件中菜单分类的名称
#define CFG_MENUITEM "CurrMenuItem" ///< 配置文件中菜单项的名称

/// @brief RGB颜色的结构体
struct RGB {
    uint8_t R; ///< 红色值 0~255
    uint8_t G; ///< 绿色值 0~255
    uint8_t B; ///< 蓝色值 0~255

    // /// @brief 将RGB值合成为32位数值
    // /// @param r 红色值 0~255
    // /// @param g 绿色值 0~255
    // /// @param b 蓝色值 0~255
    // /// @return 合成后的32位颜色值
    // static uint32_t Color(uint8_t r, uint8_t g, uint8_t b)
    // { // 返回由RGB组成的颜色
    //     return ((uint16_t)(r & 0xF8) << 8) | ((uint16_t)(g & 0xFC) << 3) | (b >> 3);
    // }

    // /// @brief 将颜色合成位32位颜色值
    // /// @return 合成后的32位颜色值
    // uint32_t Color()
    // {
    //     return Color(R, G, B);
    // }
};

#endif