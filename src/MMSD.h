/*
 * @File :  MMSD.h
 * @Time :  2024/02/13 10:34:14
 * @Vers :  1.0
 * @Desc :  SD卡访问相关的封装
 */
#ifndef _MMSD_H
#define _MMSD_H

#include "MMDefine.h"
#include "MMScr.h"
/*
  SD card connection

  This example shows how to read and write data to and from an SD card file
  The circuit:
   SD card attached to SPI bus as follows:
   // Arduino-pico core
   ** MISO - pin 16
   ** MOSI - pin 19
   ** CS   - pin 17
   ** SCK  - pin 18

   // Arduino-mbed core
   ** MISO - pin 4
   ** MOSI - pin 3
   ** CS   - pin 5
   ** SCK  - pin 2
*/

// 将图片保存在flash中不占用ram空间
// PROGMEM prog_uint32_t m[0xFFF] = {};

class MMSD {
public:
    // 将文件位图读取到矩阵
    void DrawBitmap(String FName)
    {

        if (!SD.begin(PIN_SD_SS)) { // 打开SD
            Serial.println("Initialization failed!");
            return;
        }
        // SD卡文件对象
        File myFile = SD.open(FName, FILE_READ);
        myFile.seek(54); // 跳过bmp文件的头部信息
        uint8_t t[3]; // 颜色值的临时变量
        for (uint16_t i = 1; i <= M_HEIGHT && myFile.available(); ++i) {
            for (uint16_t j = 0; j < M_WIDTH && myFile.available(); ++j) {
                // myFile.read(&t, sizeof(t)); // 读取一个像素的颜色值
                myFile.read(&t, 3);

                // Serial.println(String(t.R) + ',' + String(t.G) + ',' + String(t.B) + ' ');
                mmscr.SetPixel(j, M_HEIGHT - i, t[2], t[1], t[1]);
            }
            // Serial.println("");
        }
        // mmscr.Update();
        myFile.close();
        SD.end();
    }

} mmsd;

#endif