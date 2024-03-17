/*
 * @File :  MMMain.hpp
 * @Time :  2024/02/20 16:10:24
 * @Auth :
 * @Vers :  1.0
 * @Desc :  MagicMatrix 主程序类
 */

#ifndef _MMMAIN_HPP
#define _MMMAIN_HPP

#include "MMDebug.hpp"
#include "MMDefine.hpp"
#include "MMFill.hpp"
#include "MMGrap.hpp"
#include "MMRamBmp.hpp"
#include "MMSD.hpp"

#include "MMCommand.hpp"
#include "MMConfig.hpp"
#include "MMFPSetup.hpp"
#include "MMFunc/MMFuncPool.hpp"
#include "MMHardware.hpp"
#include "MMMenu.hpp"
#include "Scheduler.h"

// MagicMatrix 主程序类
class MMMain : InquireDelay {
    unsigned long LastPIRR = 0; // 最后检测到人体的时间

public:
    uint8_t CurrBright = M_BRIGHT; // 当前亮度，避免重复刷新
    uint8_t NextBright = M_BRIGHT; // 下一个亮度

    // 构造
    MMMain() {};
    // 析构
    // ~MMMain() {    };

    // 设置最后检测到时间
    void RenewPIRR()
    {
        this->LastPIRR = millis();
    }

    // 更新最后检测到人体时间
    void UpdatePIRR()
    {
        if (mmhardware.GetPIRR()) {
            this->RenewPIRR();
            // UART_USB.println("Got");
        }
    }

    // 更新显示屏亮度
    void UpdateBrightness()
    {
        // 获取距离上次点亮屏幕的时间
        unsigned long pass = mmhardware.TickPassed(this->LastPIRR, millis());
        // 根据检测到人体的情况修改屏幕亮度
        if (pass < M_PIRR_DELAY) {
            this->NextBright = M_BRIGHT;
        } else {
            this->NextBright = M_BIRGHT_STANDBY;
        }
        // 如果需要改变亮度则更改并刷新
        if (this->NextBright != this->CurrBright) {
            this->CurrBright = this->NextBright;
            mmhardware.matrix.setBrightness(this->CurrBright);
            mmhardware.matrix.show();
        }
    }

    // 根据人体检测设置亮度
    void CheckPIRR()
    {
        this->UpdatePIRR(); // 如果检测到人，记录当前上电时间
        this->UpdateBrightness();
    }

    // 将红外线收到的按键值转换为数值
    int IRRVal(uint16_t IRRCode)
    {
        int r = -1;
        switch (IRRCode) {
        case IRK_0:
            r = 0;
            break;
        case IRK_1:
            r = 1;
            break;
        case IRK_2:
            r = 2;
            break;
        case IRK_3:
            r = 3;
            break;
        case IRK_4:
            r = 4;
            break;
        case IRK_5:
            r = 5;
            break;
        case IRK_6:
            r = 6;
            break;
        case IRK_7:
            r = 7;
            break;
        case IRK_8:
            r = 8;
            break;
        case IRK_9:
            r = 9;
            break;
        }
        return r;
    }

    // 接收并设置当前菜单位置，返回红外线值
    bool IRRSetMenu(uint16_t& IRRCode)
    {
        bool r = false;
        if (mmhardware.IRRCode(IRRCode)) {
            this->RenewPIRR(); // 刷新检测到人体的时间
            this->UpdateBrightness(); // 更新当前亮度

            switch (IRRCode) {
            case IRK_A: // A类功能
                mmmenu.NextMenuCate = 0;
                mmmenu.NextMenuItem = 0;
                r = true;
                break;
            case IRK_B: // B类功能
                mmmenu.NextMenuCate = 1;
                mmmenu.NextMenuItem = 0;
                r = true;
                break;
            case IRK_C: // C类功能
                mmmenu.NextMenuCate = 2;
                mmmenu.NextMenuItem = 0;
                r = true;
                break;
            case IRK_D: // D类功能
                mmmenu.NextMenuCate = 3;
                mmmenu.NextMenuItem = 0;
                r = true;
                break;
            case IRK_E: // E类功能
                mmmenu.NextMenuCate = 4;
                mmmenu.NextMenuItem = 0;
                r = true;
                break;
            default:
                int t = this->IRRVal(IRRCode); // 将IRRCode专函为具体的数字
                // UART_USB.println(String(CurrMenuItem) + " " + String(NextMenuItem));
                if (mmmenu.ItemExists(mmmenu.CurrMenuCate, t)) {
                    mmmenu.NextMenuItem = t;
                    r = true;
                }
            }
        }
        return r;
    }

    // 处理USB串口信息
    void ProcUART(UART& uart)
    {
        // 如果串口收到数据
        if (uart.available()) {
            String cmd = "";
            // while (uart.available()) {
            //     cmd += char(uart.read());
            // }
            cmd = uart.readString();
            mmcommand.Exec(cmd);
        }
    }

    // 实现InquireDelay方法
    virtual bool Inquire(uint16_t& IRRCode)
    {
        this->ProcUART(UART_USB); // 处理USB串口
        this->ProcUART(UART_BLE); // 处理BLE串口
        
        // this->CheckPIRR(); // 由于功能块内部需要调用红外线数据，取消此部分多线程处理
        this->IRRSetMenu(IRRCode);
        yield(); // 释放资源
        return (mmmenu.NextMenuItem == mmmenu.CurrMenuItem && mmmenu.NextMenuCate == mmmenu.CurrMenuCate);
    }

    // 实现InquireDelay方法
    virtual bool Inquire()
    {
        uint16_t IRRCode;
        return Inquire(IRRCode);
    }

    // 实现IDelay方法
    virtual bool IDelay(unsigned long ms, uint16_t& IRRCode)
    {
        bool r = true; // 默认结果为true
        unsigned long startm = millis(); // 记录函数开始时的运行毫秒数
        unsigned long pass = 0; // 逝去的毫秒数
        do {
            delay(10);
            if (!Inquire(IRRCode)) {
                r = false;
                break;
            }
            // 过去的时间
            pass = mmhardware.TickPassed(startm, millis());
        } while (pass < ms);
        return r;
    }

    // 实现IDelay方法
    virtual bool IDelay(unsigned long ms)
    {
        uint16_t IRRCode;
        return this->IDelay(ms, IRRCode);
    }

    uint16_t ExecMenu(uint8_t CateID, uint8_t ItemID)
    {
        return mmmenu.ExecItem(CateID, ItemID, this);
    }

    // 主循环
    // 左右选择大项,数字键用来选择子项目,一个大项目下面最多包含10个子项目
    void MainLoop();

    void SetBLEName() {
        // UART_BLE.print("AT+NAME=MagicMatrix\r\n"); // 设置蓝牙名称
        UART_BLE.print("AT+MAC?\r\n"); // 先获得蓝牙的硬件地址
        String s = UART_BLE.readString();
        UART_USB.println(s.substring(13));
        // 将蓝牙的硬件地址追加并修改该蓝牙名称
        UART_BLE.print("AT+NAME=MagicMatri_" + s.substring(13) + "\r\n");
        UART_USB.println(UART_BLE.readString());
    }

    // 执行初始化
    bool Init()
    {
        pinMode(PIN_BUZZER, OUTPUT); // 设置蜂鸣器引脚
        mmhardware.Beep(true);
        uint16_t r = 0;
        UART_USB.begin(115200); // 打开串口通信
        UART_USB.setTimeout(10); // 设置串口读取超时
        UART_BLE.begin(9600); // 打开串口1，蓝牙蓝牙模块通信
        UART_BLE.setTimeout(100);
        // while(!UART_BLE);
        this->SetBLEName();
        mmhardware.Init(); // 执行硬件初始化
        mmconfig.Load(); // 读取配置信息
        // 将当前设置菜单项读取
        mmmenu.NextMenuCate = mmconfig.Config[CFG_MENUCATE];
        mmmenu.NextMenuItem = mmconfig.Config[CFG_MENUITEM];

        // 调用功能池初始化
        MMFPSetup();
        mmhardware.Beep(false);
        return r;
    }

} mmmain;

// 主循环
void MMMain::MainLoop()
{

    for (;;) {
        // 切换菜单
        mmmenu.Switch(this);
        this->Inquire();
    }
}

#endif