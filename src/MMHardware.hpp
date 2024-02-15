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

class MMHardware {
private:
    /* data */
public:
    // 定义红外接收对象
    IRrecv irrecv;
    ThreeWire myWire;
    RtcDS1302<ThreeWire> Rtc;
    // 构造函数
    MMHardware()
        : irrecv(PIN_IRR) // 构造irrecv
        , myWire(PIN_I2C_DAT, PIN_I2C_CLK, PIN_DS1302_CS)
        , Rtc(myWire)
    {
        irrecv.enableIRIn();
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
