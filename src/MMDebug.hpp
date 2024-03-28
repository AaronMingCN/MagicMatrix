/**
 * @file MMDebug.hpp
 * @date 2024/02/13 10:31:50
 * @author Aaron Ming
 * @version 1.0
 * @brief 调试相关功能
 * @details 设备相关的调试
 */

#include "MMDefine.hpp"

#ifdef MMDEBUG // 如果打开调试

#ifndef _MMDEBUG_HPP
#define _MMDEBUG_HPP

#include <ArduinoJson.h>

#include "MMGrap.hpp"
#include "MMHardware.hpp"
#include "MMRamBmp.hpp"
#include "MMSD.hpp"
#include "MMScr.hpp"

/// @brief 调试相关功能类
class MMDebug {
public:
    /// @brief 测试红外线接收
    void TestIRR()
    {
        UART_USB.println(mmhardware.IRRCode());
        delay(100);
    }

    /// @brief 测试RTC显示时间
    void TestRTC()
    {
        char buff[26] = {};
        RtcDateTime now = mmhardware.Rtc.GetDateTime();
        sprintf(buff, "%04d-%02d-%02d %02d:%02d:%02d",
            now.Year(), now.Month(), now.Day(),
            now.Hour(), now.Minute(), now.Second());
        UART_USB.println(buff);
    }

    /// @brief 测试SD卡文件访问
    void TestSD()
    {
#if defined(ARDUINO_ARCH_MBED)
        UART_USB.print("Starting SD Card ReadWrite on MBED ");
#else
        UART_USB.print("Starting SD Card ReadWrite on ");
#endif
        // SD卡文件对象
        File myFile;
        UART_USB.println(BOARD_NAME);
        UART_USB.println(RP2040_SD_VERSION);

        UART_USB.print("Initializing SD card with SS = ");
        UART_USB.println(PIN_SD_SS);
        UART_USB.print("SCK = ");
        UART_USB.println(PIN_SD_SCK);
        UART_USB.print("MOSI = ");
        UART_USB.println(PIN_SD_MOSI);
        UART_USB.print("MISO = ");
        UART_USB.println(PIN_SD_MISO);

        if (!SD.begin(PIN_SD_SS)) {
            UART_USB.println("SD Initialization failed!");
            return;
        }

        UART_USB.println("SD Initialization done.");

#define fileName "newtest0.txt"
        char writeData[] = "Testing writing to " fileName;

        // open the file. note that only one file can be open at a time,
        // so you have to close this one before opening another.
        myFile = SD.open(fileName, FILE_WRITE);

        // if the file opened okay, write to it:
        if (myFile) {
            UART_USB.print("Writing to ");
            UART_USB.print(fileName);
            UART_USB.print(" ==> ");
            UART_USB.println(writeData);

            myFile.println(writeData);

            // close the file:
            myFile.close();
            UART_USB.println("done.");
        } else {
            // if the file didn't open, print an error:
            UART_USB.print("Error opening ");
            UART_USB.println(fileName);
        }

        // re-open the file for reading:
        myFile = SD.open(fileName, FILE_READ);

        if (myFile) {
            UART_USB.print("Reading from ");
            UART_USB.println(fileName);
            UART_USB.println("===============");

            // read from the file until there's nothing else in it:
            // while (myFile.available())
            // {
            UART_USB.write(myFile.read());
            // }

            // close the file:
            myFile.close();

            UART_USB.println("===============");
        } else {
            // if the file didn't open, print an error:
            UART_USB.print("Error opening ");
            UART_USB.println(fileName);
        }
    }

    /// @brief 测试温湿度显示
    void TestDHT()
    {
        UART_USB.println(F("DHTxx Unified Sensor Example"));
        // Print temperature sensor details.
        sensor_t sensor;
        mmhardware.dht.temperature().getSensor(&sensor);
        UART_USB.println(F("------------------------------------"));
        UART_USB.println(F("Temperature Sensor"));
        UART_USB.print(F("Sensor Type: "));
        UART_USB.println(sensor.name);
        UART_USB.print(F("Driver Ver:  "));
        UART_USB.println(sensor.version);
        UART_USB.print(F("Unique ID:   "));
        UART_USB.println(sensor.sensor_id);
        UART_USB.print(F("Max Value:   "));
        UART_USB.print(sensor.max_value);
        UART_USB.println(F("°C"));
        UART_USB.print(F("Min Value:   "));
        UART_USB.print(sensor.min_value);
        UART_USB.println(F("°C"));
        UART_USB.print(F("Resolution:  "));
        UART_USB.print(sensor.resolution);
        UART_USB.println(F("°C"));
        UART_USB.println(F("------------------------------------"));
        // Print humidity sensor details.
        mmhardware.dht.humidity().getSensor(&sensor);
        UART_USB.println(F("Humidity Sensor"));
        UART_USB.print(F("Sensor Type: "));
        UART_USB.println(sensor.name);
        UART_USB.print(F("Driver Ver:  "));
        UART_USB.println(sensor.version);
        UART_USB.print(F("Unique ID:   "));
        UART_USB.println(sensor.sensor_id);
        UART_USB.print(F("Max Value:   "));
        UART_USB.print(sensor.max_value);
        UART_USB.println(F("%"));
        UART_USB.print(F("Min Value:   "));
        UART_USB.print(sensor.min_value);
        UART_USB.println(F("%"));
        UART_USB.print(F("Resolution:  "));
        UART_USB.print(sensor.resolution);
        UART_USB.println(F("%"));
        UART_USB.println(F("------------------------------------"));
        // Get temperature event and print its value.
        sensors_event_t event;
        mmhardware.dht.temperature().getEvent(&event);
        if (isnan(event.temperature)) {
            UART_USB.println(F("Error reading temperature!"));
        } else {
            UART_USB.print(F("Temperature: "));
            UART_USB.print(event.temperature);
            UART_USB.println(F("°C"));
        }
        // Get humidity event and print its value.
        mmhardware.dht.humidity().getEvent(&event);
        if (isnan(event.relative_humidity)) {
            UART_USB.println(F("Error reading humidity!"));
        } else {
            UART_USB.print(F("Humidity: "));
            UART_USB.print(event.relative_humidity);
            UART_USB.println(F("%"));
        }
    }

    /// @brief 测试RamBmp使用
    void TestMMRamBmp()
    {
        MMRamBmp rb;

        for (uint16_t i = 0; i < M_HEIGHT; i++) {
            for (uint16_t j = 0; j < M_WIDTH; j++) {
                if (j == i)
                    rb.SetPixel(j, i, 255, 0, 0);
                mmscr.DrawRamBmp(rb);
            }
        }
        mmscr.Update();
        delay(1000);
    }

    /// @brief 测试json使用
    void TestJSON()
    {
        // Allocate the JSON document
        JsonDocument doc;

        // Add values in the document
        doc["sensor"] = "gps";
        doc["time"] = 1351824120;

        // Add an array
        JsonArray data = doc["data"].to<JsonArray>();
        data.add(48.756080);
        data.add(2.302038);

        // Generate the minified JSON and send it to the Serial port
        serializeJson(doc, UART_USB);
        // The above line prints:
        // {"sensor":"gps","time":1351824120,"data":[48.756080,2.302038]}

        // Start a new line
        UART_USB.println();

        // Generate the prettified JSON and send it to the Serial port
        serializeJsonPretty(doc, UART_USB);
        // The above line prints:
        // {
        //   "sensor": "gps",
        //   "time": 1351824120,
        //   "data": [
        //     48.756080,
        //     2.302038
        //   ]
        // }
        mmsd.SaveJsonToFile(doc, "111.js");
    }

    /// @brief 测试绘制mm字符
    void TestDispMMChar()
    {
        mmgrap.DrawChar(0, 0, CHAR_0, &mmscr, MMCStyle::Styles[0]);
        mmgrap.DrawChar(4, 0, CHAR_1, &mmscr, MMCStyle::Styles[0]);
        mmgrap.DrawChar(8, 0, CHAR_2, &mmscr, MMCStyle::Styles[0]);
        mmgrap.DrawChar(12, 0, CHAR_3, &mmscr, MMCStyle::Styles[0]);

        mmgrap.DrawChar(0, 6, CHAR_5, &mmscr, MMCStyle::Styles[1]);
        mmgrap.DrawChar(4, 6, CHAR_6, &mmscr, MMCStyle::Styles[1]);
        mmgrap.DrawChar(8, 6, CHAR_7, &mmscr, MMCStyle::Styles[1]);
        mmgrap.DrawChar(12, 6, CHAR_8, &mmscr, MMCStyle::Styles[1]);

        mmscr.Update();
    }

} mmdebug;

#endif

#endif