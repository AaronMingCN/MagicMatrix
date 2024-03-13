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

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>

#include <DHT.h>
#include <DHT_U.h>

// 使用互斥避免线程中资源访问冲突
#include <mutex>

// 定义选择时钟使用的芯片
// #define MM_RTCDS1302
#define MM_RTCDS1307
#ifdef MM_RTCDS1302
#include <RtcDS1302.h>
#endif

#ifdef MM_RTCDS1307
#include <RtcDS1307.h>
#endif

// 定义串口
#define UART_USB _UART_USB_
#define UART_BLE _UART1_

class MMHardware {
public:
    IRrecv irrecv; // 定义红外接收对象
    DHT_Unified dht; // 定义dht温湿度模块
#ifdef MM_RTCDS1302
    ThreeWire myWire; // 定义i2c通信模块
    RtcDS1302<ThreeWire> Rtc; // 定义rtc时钟模块
#endif
#ifdef MM_RTCDS1307
    RtcDS1307<TwoWire> Rtc;
#endif
    Adafruit_NeoMatrix matrix; // 矩阵模块

    std::recursive_mutex SDMutex; // sd访问的互斥

    uint16_t IRRLastTime; // 最后一次接收到红外线数据的事件，用于防止连击
    // 构造函数
    MMHardware()
        : irrecv(PIN_IRR) // 构造irrecv
        , dht(PIN_DHT, DHT11) // 构造dht温湿度模块
#ifdef MM_RTCDS1302
        , myWire(PIN_I2C_DAT, PIN_I2C_CLK, PIN_DS1302_CS) // 构造i2c通信
        , Rtc(myWire) // 构造rtc时钟模块
#endif
#ifdef MM_RTCDS1307
        , Rtc(Wire) // 构造rtc时钟模块
#endif
        , matrix(M_HEIGHT, M_WIDTH, PIN_M, M_MATRIXTYPE, M_LEDTYPE) {
            // Init(); // 放在main类中初始化，否则会引起系统异常
        };
    // ~MMHardware();

    // 用于计算经过的时间，考虑环绕的情况，毫秒或者微妙
    unsigned long TickPassed(unsigned long From, unsigned long To)
    {
        unsigned long r = 0;
        if (To >= From)
            r = (To - From); // 如果没有出现环绕
        else
            r = ((unsigned long)(-1) - From) + To; // 如果出现环绕
        return r;
    }

    void Init()
    {


        irrecv.enableIRIn(); // 打开红外接收
        dht.begin(); // 温湿度传感器开始工作
        matrix.begin(); // 矩阵屏幕开始工作
        matrix.setTextWrap(false); // 矩阵显示设置为不自动换行
        matrix.setBrightness(M_BRIGHT); // 设置矩阵屏幕亮度0~255
        Rtc.Begin(); // 打开Rtc时间模块


        pinMode(PIN_PIRR, INPUT); // 设置人体红外探测器为输入
        // matrix.setRotation(3); // 设置屏幕旋转角度

    }

    // IRRCode红外线读取到的结果代码, WaitData 是否等待数据
    bool IRRCode(uint16_t& Code, bool WaitData = false)
    {
        uint16_t r = false;
        Code = IRK_NONE;
        // 如果需要等待数据
        if (WaitData) {
            while (!(this->irrecv.decode()))
                delay(10);
            r = true;
            Code = this->irrecv.decodedIRData.command;
            this->irrecv.resume();
        } else {
            if (this->irrecv.decode()) { // 如果红外线读取到数据
                r = true;
                Code = this->irrecv.decodedIRData.command;
                this->irrecv.resume();
            }
        }
        return r;
    }

    uint16_t IRRCode(bool WaitData = false)
    {
        uint16_t r;
        this->IRRCode(r, WaitData);
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
