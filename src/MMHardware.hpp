/*
 * @File :  MMHardware.hpp
 * @Time :  2024/02/15 20:55:12
 * @Auth :
 * @Vers :  1.0
 * @Desc :  MagicMatrix硬件访问类
 */

#ifndef _MM_HARDWARE_HPP
#define _MM_HARDWARE_HPP

#include "MMDefine.hpp"
#include <IRremote.hpp>
#include <RtcDS1302.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>


class MMHardware {
private:
    /* data */
public:
    IRrecv irrecv; // 定义红外接收对象
    ThreeWire myWire; // 定义i2c通信模块
    RtcDS1302<ThreeWire> Rtc; // 定义rtc时钟模块
    DHT_Unified dht; // 定义dht温湿度模块
    // 构造函数
    MMHardware()
        : irrecv(PIN_IRR) // 构造irrecv
        , myWire(PIN_I2C_DAT, PIN_I2C_CLK, PIN_DS1302_CS) // 构造i2c通信
        , Rtc(myWire) // 构造rtc时钟模块
        , dht(PIN_DHT, DHT11) // 构造dht温湿度模块
    {
        irrecv.enableIRIn(); // 打开红外接收
        dht.begin(); // 打开dht温湿度传感器
    };
    // ~MMHardware();

    // IRRCode红外线读取到的结果代码
    uint16_t IRRCode()
    {
        uint16_t r = IRK_NONE;
        if (this->irrecv.decode()) { // 如果红外线读取到数据
            r = this->irrecv.decodedIRData.command;
            this->irrecv.resume();
        }
        return r;
    }

} mmhardware;

#endif
