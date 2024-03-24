/**
 * @file MagicMatrix.cpp
 * @date 2024/02/13 10:32:36
 * @version 1.0
 * @author Aaron Ming
 * @brief 主程序
 * @details MagicMatrix魔法矩阵,系统入口程序
 */
#include "MMDebug.hpp"

#include "MMHardware.hpp"
#include "MMMain.hpp"

#include "MMFunc/MMFuncPool.hpp"
#include "MMConfig.hpp"

#include <Scheduler.h>
#include "MMGrap.hpp"

// // 由于功能块内部需要调用红外线数据，取消此部分多线程处理，
// // 事件循环

/// @brief 事件循环
/// @note 此函数用于响应红外设备等事件一级保存设置等事件，在主循环外的线程中执行 
/// @attention 多线程执行，需要考虑线程同步问题
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

    // delay(2000);

    // UART_USB.println(__DATE__);
    // UART_USB.println(__TIME__);
    
}

