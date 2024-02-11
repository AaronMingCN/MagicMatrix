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

  }

} mmsd;

#endif