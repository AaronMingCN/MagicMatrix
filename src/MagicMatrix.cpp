/*
 * @File :  MagicMatrix.cpp
 * @Time :  2024/02/13 10:32:36
 * @Vers :  1.0
 * @Desc :  MagicMatrix魔法矩阵,主程序
 */

#include "MMDebug.hpp"

#include "MMHardware.hpp"
#include "MMMain.hpp"

#include "MMFunc/MMFuncPool.hpp"

void setup()
{
    delay(1000); // 等待一秒bootloader
    // 系统初始化
    mmmain.Init();
    // 取消注释后会根据编译时间调整硬件时间
    mmhardware.Rtc.SetDateTime(RtcDateTime(__DATE__, __TIME__));
}

void loop()
{
    // 执行主循环
    mmmain.MainLoop();
}
