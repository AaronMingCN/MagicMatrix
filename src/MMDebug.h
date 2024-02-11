#include "MMDefine.h"
#include "MMScr.h"

#ifdef MMDEBUG // 如果打开调试

class MMDebug {
public:

    // 测试RTC显示时间
    void TestRTC() {
        char buff[20] = {};
        RtcDateTime now = Rtc.GetDateTime();
        sprintf(buff, "%04d-%02d-%02d %02d:%02d:%02d", 
            now.Year(), now.Month(), now.Day(),
            now.Hour(), now.Minute(), now.Second());
        Serial.println(buff);
    }
    
  // 测试SD卡文件访问
  void TestSD() {
    #if defined(ARDUINO_ARCH_MBED)
    Serial.print("Starting SD Card ReadWrite on MBED ");
    #else
    Serial.print("Starting SD Card ReadWrite on ");
    #endif
    //SD卡文件对象
    File myFile;
    Serial.println(BOARD_NAME);
    Serial.println(RP2040_SD_VERSION);
    
    Serial.print("Initializing SD card with SS = ");  Serial.println(PIN_SD_SS);
    Serial.print("SCK = ");   Serial.println(PIN_SD_SCK);
    Serial.print("MOSI = ");  Serial.println(PIN_SD_MOSI);
    Serial.print("MISO = ");  Serial.println(PIN_SD_MISO);

    if (!SD.begin(PIN_SD_SS)) 
    {
        Serial.println("Initialization failed!");
        return;
    }
    
    Serial.println("Initialization done.");

    #define fileName  "newtest0.txt"
    char writeData[]  = "Testing writing to " fileName;
    
    // open the file. note that only one file can be open at a time,
    // so you have to close this one before opening another.
    myFile = SD.open(fileName, FILE_WRITE);

    // if the file opened okay, write to it:
    if (myFile) 
    {
        Serial.print("Writing to "); Serial.print(fileName); 
        Serial.print(" ==> "); Serial.println(writeData);

        myFile.println(writeData);
        
        // close the file:
        myFile.close();
        Serial.println("done.");
    } 
    else 
    {
        // if the file didn't open, print an error:
        Serial.print("Error opening "); Serial.println(fileName);
    }

    // re-open the file for reading:
    myFile = SD.open(fileName, FILE_READ);
    
    if (myFile) 
    {
        Serial.print("Reading from "); Serial.println(fileName);
        Serial.println("===============");

        // read from the file until there's nothing else in it:
        // while (myFile.available()) 
        // {
        Serial.write(myFile.read());
        // }

        // close the file:
        myFile.close();

        Serial.println("===============");
    } 
    else 
    {
        // if the file didn't open, print an error:
        Serial.print("Error opening "); Serial.println(fileName);
    }
  }
} mmdebug;


#endif