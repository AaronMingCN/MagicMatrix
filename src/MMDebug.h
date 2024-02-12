#include "MMDefine.h"
#include "MMScr.h"

#ifdef MMDEBUG // 如果打开调试

class MMDebug {
public:

    // 测试RTC显示时间
    void TestRTC() {
        char buff[26] = {};
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


  void TestDHT(){
    Serial.println(F("DHTxx Unified Sensor Example"));
    // Print temperature sensor details.
    sensor_t sensor;
    dht.temperature().getSensor(&sensor);
    Serial.println(F("------------------------------------"));
    Serial.println(F("Temperature Sensor"));
    Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
    Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
    Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
    Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
    Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
    Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
    Serial.println(F("------------------------------------"));
    // Print humidity sensor details.
    dht.humidity().getSensor(&sensor);
    Serial.println(F("Humidity Sensor"));
    Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
    Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
    Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
    Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
    Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
    Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
    Serial.println(F("------------------------------------"));
    // Get temperature event and print its value.
    sensors_event_t event;
    dht.temperature().getEvent(&event);
    if (isnan(event.temperature)) {
        Serial.println(F("Error reading temperature!"));
    }
    else {
        Serial.print(F("Temperature: "));
        Serial.print(event.temperature);
        Serial.println(F("°C"));
    }
    // Get humidity event and print its value.
    dht.humidity().getEvent(&event);
    if (isnan(event.relative_humidity)) {
        Serial.println(F("Error reading humidity!"));
    }
    else {
        Serial.print(F("Humidity: "));
        Serial.print(event.relative_humidity);
        Serial.println(F("%"));
    }

  }
} mmdebug;


#endif