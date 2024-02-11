// 统一定义

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <IRremote.hpp>
#include <RtcDS1302.h>


#ifndef MMDEF
#define MMDEF // Make Arduino Due happy

  #define MMDEBUG // 定义调试宏用于控制调试输出

  #define C_RP2040 // 定义使用的芯片类型

  #ifdef C_RP2040
    #define PIN_M (2) // 定义矩阵屏幕引脚
    #define PIN_IRR (22) // 定义红外线接收引脚

    #define PIN_I2C0_DAT (4) // I2C数据引脚
    #define PIN_I2C0_CLK (5) // I2C时钟引脚

    #define PIN_DS1302_CS (6) // DS1302选择引脚 

    #define PIN_SD_CS PIN_SPI0_CS // sd卡使能引脚

    // 定义SD访问相关的引脚
    #if !defined(ARDUINO_ARCH_RP2040) 
      #error For RP2040 only
    #endif
    
    // SS = 17
    // SCK = 18
    // MOSI = 19
    // MISO = 16

    #if defined(ARDUINO_ARCH_MBED) 
      
      #define PIN_SD_MOSI       PIN_SPI_MOSI
      #define PIN_SD_MISO       PIN_SPI_MISO
      #define PIN_SD_SCK        PIN_SPI_SCK
      #define PIN_SD_SS         PIN_SPI_SS

    #else

      #define PIN_SD_MOSI       PIN_SPI0_MOSI
      #define PIN_SD_MISO       PIN_SPI0_MISO
      #define PIN_SD_SCK        PIN_SPI0_SCK
      #define PIN_SD_SS         PIN_SPI0_SS
      
    #endif

    #define _RP2040_SD_LOGLEVEL_       4

    #include <SPI.h>
    #include <RP2040_SD.h>

  #endif

#define M_8x8

#ifdef M_8x8
  #define M_ROW (8) // 定义矩阵屏幕行数 
  #define M_COL (8) // 定义矩阵屏幕列数
    // 定义RGB矩阵
  Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(M_COL, M_ROW, PIN_M,
    NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
    NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
    NEO_GRB            + NEO_KHZ800);
#else
  #define M_ROW (16) // 定义矩阵屏幕行数 
  #define M_COL (16) // 定义矩阵屏幕列数
    // 定义RGB矩阵
  Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(M_ROW, M_COL, PIN_M,
    NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
    NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
    NEO_GRB            + NEO_KHZ800);  
#endif

#define M_PIXS (M_ROW * M_COL) // 定义矩阵像素数
#define M_BRIGHT (30) // 屏幕亮度0~255


// 定义红外接收对象
IRrecv irrecv(PIN_IRR);

// 定义时钟引脚
ThreeWire myWire(PIN_I2C0_DAT ,PIN_I2C0_CLK, PIN_DS1302_CS); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);

// 定义红外遥控器的按键
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
  uint32_t Color() { // 返回由RGB组成的颜色
    return matrix.Color(R,G,B);
  }  
};




#endif