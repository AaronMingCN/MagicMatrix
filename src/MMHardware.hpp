/**
 * @file MMHardware.hpp
 * @date 2024/02/15 20:55:12
 * @author Aaron Ming
 * @version 1.0
 * @brief 硬件访问
 * @details 将硬件统一管理
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

/// 定义选择时钟使用的芯片
#define MM_RTCDS1302
// #define MM_RTCDS1307

#ifdef MM_RTCDS1302
#include <RtcDS1302.h>
#endif

#ifdef MM_RTCDS1307
#include <RtcDS1307.h>
#endif

/// 定义USB串口
#define UART_USB _UART_USB_
/// 定义蓝牙串口
#define UART_BLE _UART1_

/// @brief 硬件类
class MMHardware {

public:
    IRrecv irrecv; ///< 定义红外接收对象
    DHT_Unified dht; ///< 定义dht温湿度模块
#ifdef MM_RTCDS1302
    ThreeWire myWire; ///< 定义i2c通信模块
    RtcDS1302<ThreeWire> Rtc; ///< 定义rtc时钟模块
#endif
#ifdef MM_RTCDS1307
    RtcDS1307<TwoWire> Rtc;
#endif
    Adafruit_NeoMatrix matrix; ///< 矩阵模块

    /// @brief 构造函数
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

    /// @brief 计算经过的时间
    /// @param From 开始时间
    /// @param To 结束时间
    /// @return 经过的时间
    /// @details 计算经过的时间，考虑环绕的情况，毫秒或者微妙
    unsigned long TickPassed(unsigned long From, unsigned long To)
    {
        unsigned long r = 0;
        if (To >= From)
            r = (To - From); // 如果没有出现环绕
        else
            r = ((unsigned long)(-1) - From) + To; // 如果出现环绕
        return r;
    }

    /// @brief 初始化硬件
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

    /// @brief 读取红外遥控编码
    /// @param[out] Code 读取到的编码
    /// @param WaitData 是否等待接收到编码
    /// @return 是否收到编码
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

    /// @brief 读取红外遥控编码
    /// @param WaitData 是否等待接收编码
    /// @return 接收到的编码
    uint16_t IRRCode(bool WaitData = false)
    {
        uint16_t r;
        this->IRRCode(r, WaitData);
        return r;
    }

    /// @brief 设置蜂鸣器状态
    /// @param val 状态:true 打开，false 关闭
    void Beep(bool val)
    {
        digitalWrite(PIN_BUZZER, val);
    }

    /// @brief 读取人体红外探测器状态
    bool GetPIRR()
    {
        return digitalRead(PIN_PIRR);
    }

    /// @brief 设置日期时间
    /// @param year 年
    /// @param month 月
    /// @param dayOfMonth 日
    /// @param hour 时
    /// @param minute 分
    /// @param second 秒
    void SetDateTime(uint16_t year,
        uint8_t month,
        uint8_t dayOfMonth,
        uint8_t hour,
        uint8_t minute,
        uint8_t second)
    {
        this->Rtc.SetDateTime(RtcDateTime(year, month, dayOfMonth, hour, minute, second));
    }

    /// @brief 设置日期时间
    /// @param date 日期
    /// @param time 时间
    /// @note sample input: date = "Dec 06 2009", time = "12:34:56"
    void SetDateTime(const char* date, const char* time)
    {
        this->Rtc.SetDateTime(RtcDateTime(date, time));
    }

} mmhardware;

#endif
