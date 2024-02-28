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
// #include <RtcDS1302.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <RtcDS1307.h>

class MMHardware {
public:
    IRrecv irrecv; // 定义红外接收对象
    DHT_Unified dht; // 定义dht温湿度模块
    // ThreeWire myWire; // 定义i2c通信模块
    // RtcDS1302<ThreeWire> Rtc; // 定义rtc时钟模块
    RtcDS1307<TwoWire> Rtc;
    Adafruit_NeoMatrix matrix;

    uint16_t IRRLastTime; // 最后一次接收到红外线数据的事件，用于防止连击
    // 构造函数
    MMHardware()
        : irrecv(PIN_IRR) // 构造irrecv
        , dht(PIN_DHT, DHT11) // 构造dht温湿度模块
        // , myWire(PIN_I2C_DAT, PIN_I2C_CLK, PIN_DS1302_CS) // 构造i2c通信
        // , Rtc(myWire) // 构造rtc时钟模块
        , Rtc(Wire) // 构造rtc时钟模块
        , matrix(M_HEIGHT, M_WIDTH, PIN_M, M_MATRIXTYPE, M_LEDTYPE) {
            // Init(); // 放在main类中初始化，否则会引起系统异常
        };
    // ~MMHardware();

    void Init()
    {
        irrecv.enableIRIn(); // 打开红外接收
        dht.begin(); // 温湿度传感器开始工作
        matrix.begin(); // 矩阵屏幕开始工作
        matrix.setTextWrap(false); // 矩阵显示设置为不自动换行
        matrix.setBrightness(M_BRIGHT); // 设置矩阵屏幕亮度0~255
        Rtc.Begin(); // 打开Rtc时间模块
        // while (!matrix.availableForWrite()) delay(100); // 等待设备就绪
        // while (!irrecv.available()) delay(100);
        pinMode(PIN_BUZZER, OUTPUT); // 设置蜂鸣器引脚
        pinMode(PIN_PIRR, INPUT); // 设置人体红外探测器为输入
    }

    // IRRCode红外线读取到的结果代码, WaitRelease 是否等待松开按键
    uint16_t IRRCode(bool WaitRelease = false)
    {
        // irLibrary.check();
        uint16_t r = IRK_NONE;
        if (this->irrecv.decode()) { // 如果红外线读取到数据
            r = this->irrecv.decodedIRData.command;

            this->irrecv.resume();
        }
        if (WaitRelease) { // 如果需要等待抬起按键
            while (this->irrecv.decode()) { // 等待红外遥控抬起按键
                this->irrecv.resume();
            }
        }
        return r;
    }

    // 如果读取到了数据，等待按键抬起，防止误操作
    uint16_t IRRClickCode()
    {
        uint16_t r = IRK_NONE;
        unsigned long pass = 0; // 距离上次接收红外线的时间
        uint16_t mill = millis(); // 获取当前开机时间
        // 防止环绕的处理
        if (mill >= this->IRRLastTime)
            pass = mill - this->IRRLastTime;
        else
            pass = (unsigned long)(-1) - this->IRRLastTime + mill;
        if (pass > IRR_WAIT) { // 如果逝去的时间超过了等待间隔
            r = this->IRRCode(); // 获取红外代码
            if (r != IRK_NONE)
                this->IRRLastTime = mill; // 如果获得成功更新最后获得时间
        }
        return r;
    }

    // 设置蜂鸣器开关
    void Beep(bool val)
    {
        digitalWrite(PIN_BUZZER, val);
    }

    // 读取人体红外探测器状态
    bool GetPIRR()
    {
        return digitalRead(PIN_PIRR);
    }
} mmhardware;

#endif
