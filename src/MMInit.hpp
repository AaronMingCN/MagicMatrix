/*
 * @File :  MMInit.hpp
 * @Time :  2024/02/15 03:18:37
 * @Auth :   
 * @Vers :  1.0
 * @Desc :  系统初始化
 */

#ifndef _MMINIT_HPP
#define _MMINIT_HPP

#include "MMDebug.hpp"
#include "MMDefine.hpp"
#include "MMFill.hpp"
#include "MMGrap.hpp"
#include "MMRamBmp.hpp"
#include "MMSD.hpp"

#include "MMFPSetup.hpp"
#include "MMHardware.hpp"

uint16_t MMInit() {
    uint16_t r = 0;
    Serial.begin(19200); // 打开串口通信
    

    mmhardware.Init(); // 执行硬件初始化
    mmhardware.matrix.setBrightness(M_BRIGHT); // 设置矩阵屏幕亮度0~255

    // 调用功能池初始化
    MMFPSetup();
    // 执行功能池中的矩阵测试功能
    FPool.Exec(MMF_ID_MATRIXTEST);     
    delay(1000); 
    // 打开人体红外监测模块
    pinMode(PIN_PIR, INPUT);
    return r;  
}

#endif
