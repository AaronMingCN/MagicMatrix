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


uint16_t MMInit() {
    uint16_t r = 0;
    matrix.begin();
    // // matrix.setTextWrap(false);
    matrix.setBrightness(M_BRIGHT); // 设置矩阵屏幕亮度0~255

    mmfill.MatrixTest(); // 测试矩阵

    Serial.begin(9600); // 打开串口通信
    for (uint8_t i = 0; i < 100; ++i) { // 等待串口连接成功，防止RTOS崩溃
        if (Serial)
            break;
        delay(10);
    }
    // while(!Serial) delay(10); // 等待串口通信成功

    // matrix.setTextColor(colors[0]);
    irrecv.enableIRIn(); // 打开红外遥控接收器
    dht.begin(); // 打开dht温湿度传感器

    // 调用功能池初始化
    MMFPSetup();
    // 执行功能池中的矩阵测试功能
    FPool.Exec(MMF_ID_MATRIXTEST); 
    return r;  
}

#endif
