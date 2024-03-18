/*
 * @File :  MMSD.hpp
 * @Time :  2024/02/13 10:34:14
 * @Vers :  1.0
 * @Desc :  SD卡访问相关的封装
 */
#ifndef _MMSD_HPP
#define _MMSD_HPP

#include "MMDefine.hpp"
#include "MMRamBmp.hpp"
#include "MMScr.hpp"

#include <ArduinoJson.h>

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
private:
    bool _SDIsBusy = false; // SD是否忙碌中, 用于多线程中的访问, 互斥
public:
    ~MMSD()
    {
        SD.end();
    }

    // 获得SD访问权
    void GetLockSD()
    {
        while (this->_SDIsBusy)
            yield(); // 如果被占用则等待
        this->_SDIsBusy = true;
    }

    // 释放SD
    void ReleaseSD()
    {
        this->_SDIsBusy = false;
    }

    // 绘制位图
    void DrawBitmapFile(File& F, bool AutoShow = true)
    {
        F.seek(54); // 跳过bmp文件的头部信息
        uint8_t t[3]; // 颜色值的临时变量
        for (uint16_t i = 1; i <= M_HEIGHT && F.available(); ++i) {
            for (uint16_t j = 0; j < M_WIDTH && F.available(); ++j) {
                // myFile.read(&t, sizeof(t)); // 读取一个像素的颜色值
                F.read(&t, 3);

                // UART_USB.println(String(t.R) + ',' + String(t.G) + ',' + String(t.B) + ' ');
                mmscr.SetPixel(j, M_HEIGHT - i, t[2], t[1], t[0]);
            }
        }
        if (AutoShow)
            mmscr.Update();
    }

    // 将文件位图读取到矩阵
    bool DrawBitmapFile(String FileName, bool AutoShow = true)
    {
        bool r = false;
        this->GetLockSD(); // 获得SD访问权
        if (!SD.begin(PIN_SD_SS)) { // 打开SD
            UART_USB.println("SD Initialization failed!");
        } else {
            // SD卡文件对象
            File myFile = SD.open(FileName, FILE_READ);
            DrawBitmapFile(myFile, AutoShow);
            myFile.close();
            r = true;
            // SD.end(); // 关闭SD卡访问
        }
        this->ReleaseSD(); // 释放SD访问权
        return r;
    }

    void LoadBitmapToRamBmp(File& F, MMRamBmp& RamBmp)
    {
        F.seek(54); // 跳过bmp文件的头部信息
        uint8_t t[3]; // 颜色值的临时变量
        for (uint16_t i = 1; i <= M_HEIGHT && F.available(); ++i) {
            for (uint16_t j = 0; j < M_WIDTH && F.available(); ++j) {
                // myFile.read(&t, sizeof(t)); // 读取一个像素的颜色值
                F.read(&t, 3);
                RamBmp.SetPixel(j, M_HEIGHT - i, t[2], t[1], t[0]);
            }
        }
    }

    // 统计文件夹下的文件数量, IncludeFolders是否包含文件夹
    uint16_t FileCount(File& dir, bool IncludeFolders = false)
    {
        uint16_t r = 0; // 定义返回结果
        if (dir && dir.isDirectory()) {
            dir.rewindDirectory(); // 返回文件开始位置
            File entry; // 定义文件入口
            for (;;) {
                entry = dir.openNextFile();
                if (entry) { // 如果文件打开成功
                    if (entry.isDirectory() && IncludeFolders) { // 如果是文件夹,并且需要计数
                        ++r;
                    } else {
                        ++r;
                    }
                    entry.close(); // 关闭文件
                } else
                    break;
            }
            dir.rewindDirectory(); // 返回文件夹开始位置
        }
        return r;
    }

    // 将文件保存到MMRamBmp
    bool LoadBitmapToRamBmp(String FileName, MMRamBmp& RamBmp)
    {
        bool r = false;
        this->GetLockSD(); // 获得SD访问权
        if (!SD.begin(PIN_SD_SS)) { // 打开SD
            UART_USB.println("SD Initialization failed!");
        } else {
            // SD卡文件对象
            if (SD.exists(FileName)) {
                File myFile = SD.open(FileName, FILE_READ);
                this->LoadBitmapToRamBmp(myFile, RamBmp);
                myFile.close();
                r = true;
            }
            // SD.end(); // 关闭SD卡访问
        }
        this->ReleaseSD(); // 释放SD访问权
        return r;
    }

    // 将JSON文件保存到SD卡
    bool SaveJsonToFile(JsonDocument& Json, const char* FileName)
    {
        bool r = false; // 定义结果
        this->GetLockSD(); // 获得SD访问权
        if (!SD.begin(PIN_SD_SS)) { //
            UART_USB.println("SD Initialization failed!");
        } else {
            SD.remove(FileName); // 如果存在文件则先删除
            File myFile; // 定义文件对象
            myFile = SD.open(FileName, FILE_WRITE); // 创建写入
            // if the file opened okay, write to it:
            if (myFile) {
                // myFile.println("writeData");
                serializeJsonPretty(Json, myFile);
                // close the file:
                myFile.close();
                r = true;
                // UART_USB.println("done.");
            } else {
                // if the file didn't open, print an error:
                UART_USB.print("Error opening ");
            }
        }
        this->ReleaseSD(); // 释放SD访问权
        return r;
    }

    // 从SD卡载入JSON
    bool LoadJsonFromFile(JsonDocument& Json, const char* FileName)
    {
        bool r = false; // 定义返回结果
        this->GetLockSD(); // 获得SD访问权
        if (!SD.begin(PIN_SD_SS)) { //
            UART_USB.println("SD Initialization failed!");
        } else {
            File myFile; // 定义文件对象
            // myFile = SD.open(FileName, FILE_WRITE);
            myFile = SD.open(FileName, FILE_READ); // 创建写入
            // if the file opened okay, write to it:
            if (myFile) {
                // serializeJsonPretty(Json, myFile);
                deserializeJson(Json, myFile);
                // close the file:
                myFile.close();
                r = true;
                // UART_USB.println("done.");
            } else {
                // if the file didn't open, print an error:
                UART_USB.print("Error opening ");
            }
        }
        this->ReleaseSD(); // 释放SD访问权
        return r;
    }
} mmsd;

#endif