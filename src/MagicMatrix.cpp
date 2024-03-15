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
#include "MMConfig.hpp"

#include "Scheduler.h"
#include "MMGrap.hpp"


// // 由于功能块内部需要调用红外线数据，取消此部分多线程处理，
// // 事件循环
void EventLoop() {
    // mmmain.SetMenu(); // 更新菜单情况
    mmmain.CheckPIRR(); // 更新屏幕亮度
    mmconfig.SaveIfNeeded(); // 如果设置需要保存则保存
    Scheduler.yield(); // 释放资源
}

// 初始化
void setup()
{
    delay(1000); // 等待一秒bootloader
    // mmgrap.DispLOGO();
    // 系统初始化
    mmmain.Init();
        
    // 取消注释后会根据编译时间调整硬件时间
    // mmhardware.Rtc.SetDateTime(RtcDateTime(__DATE__, __TIME__));
    Scheduler.startLoop(EventLoop); // 开启事件循环
}

// 主循环
void loop()
{
    mmgrap.DispLOGO();
    // 执行主循环
    mmmain.MainLoop();
    // mmmain.Inquire();
    // mmdebug.TestJSON();
    // mmdebug.TestSD();
    // delay(2000);
}

