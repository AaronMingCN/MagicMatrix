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

#ifndef MMSD 
#define MMSD 

class MMSD{
public:
  // 将文件位图读取到矩阵
  void DrawBitmap(String FName) {
    if (!SD.begin(PIN_SD_SS)) { // 打开SD
        Serial.println("Initialization failed!");
        return;
    } 
    //SD卡文件对象
    mmscr.Clear();
    File myFile = SD.open(FName, FILE_READ); 
    myFile.seek(54); // 跳过bmp文件的头部信息
    RGB t = {}; // 颜色值的临时变量
    for (uint16_t i = 0; i < M_ROW && myFile.available(); ++i) {
      for (uint16_t j = 0; j < M_COL && myFile.available(); ++j) {
        // myFile.read(&t, sizeof(t)); // 读取一个像素的颜色值
        myFile.read(&(t.B), 1);
        myFile.read(&(t.G), 1);
        myFile.read(&(t.R), 1);
        
        Serial.println(String(t.R) + ',' + String(t.G) + ',' + String(t.B) + ' ');
        mmscr.SetPixel(j,i, t.R, t.G, t.B);
        mmscr.Update();
      }
      Serial.println("");
    }
    myFile.close();
    SD.end();
  }

} mmsd;

#endif