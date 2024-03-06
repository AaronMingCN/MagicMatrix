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

#include "MMFPSetup.hpp"
#include "MMFunc/MMFuncPool.hpp"
#include "MMHardware.hpp"
#include "MMMenu.hpp"
// #include "Scheduler.h"

// MagicMatrix 主程序类
class MMMain : InquireDelay {
    unsigned long LastPIRR = 0; // 最后检测到人体的时间

public:
    uint8_t CurrMenuCate = 0; // 当前所在的菜单类
    uint8_t CurrMenuItem = 0; // 当前所在的菜单项目
    uint8_t NextMenuCate = 0; // 下一个菜单类
    uint8_t NextMenuItem = 0; // 下一个菜单位置
    uint8_t CurrBright = M_BRIGHT; // 当前亮度，避免重复刷新
    uint8_t NextBright = M_BRIGHT; // 下一个亮度
    // 定义菜单
    MMMenu mmm;

    // 构造
    MMMain()
        : mmm(&mmfuncpool) {};
    // 析构
    // ~MMMain() {    };

    // 设置最后检测到时间
    void RenewPIRR() {
        this->LastPIRR = millis();
    }

    // 更新最后检测到人体时间
    void UpdatePIRR()
    {
        if (mmhardware.GetPIRR())
            this->RenewPIRR();
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

    // 接收并设置当前菜单位置
    void CheckMenu()
    {
        uint16_t IRRCode;
        if (mmhardware.IRRCode(IRRCode)) {
            this->RenewPIRR(); // 刷新检测到人体的时间
            this->UpdateBrightness(); // 更新当前亮度

            switch (IRRCode) {
            case IRK_A: // A类功能
                this->NextMenuCate = 0;
                this->NextMenuItem = 0;
                break;
            case IRK_B: // B类功能
                this->NextMenuCate = 1;
                this->NextMenuItem = 0;
                break;
            case IRK_C: // C类功能
                this->NextMenuCate = 2;
                this->NextMenuItem = 0;
                break;
            case IRK_D: // D类功能
                this->NextMenuCate = 3;
                this->NextMenuItem = 0;
                break;
            case IRK_E: // E类功能
                this->NextMenuCate = 4;
                this->NextMenuItem = 0;
                break;
            default:
                int t = this->IRRVal(IRRCode); // 读取红外数值
                // UART_USB.println(String(CurrMenuItem) + " " + String(NextMenuItem));
                if (mmm.ItemExists(this->CurrMenuCate, t))
                    this->NextMenuItem = t;
            }
        }
    }

    // 实现InquireDelay方法
    virtual bool Inquire()
    {
        // 读取蓝牙
        while (UART_BLE.available()) {
            // String s = UART_USB1.readString();
            UART_USB.print(char(UART_BLE.read()));
        }
        this->CheckPIRR(); // 由于功能块内部需要调用红外线数据，取消此部分多线程处理
        this->CheckMenu();
        // 菜单位置是否未变化
        // bool r = (NextMenuItem == CurrMenuItem && NextMenuCate == CurrMenuCate);
        // if (!r) {
        //     this->RenewPIRR(); // 刷新检测到人体的时间
        //     this->UpdateBrightness(); // 更新当前亮度
        // }
        // Scheduler.yield(); // 释放资源
        return (NextMenuItem == CurrMenuItem && NextMenuCate == CurrMenuCate);
    }

    // 实现IDelay方法
    virtual bool IDelay(unsigned long ms)
    {
        bool r = true; // 默认结果为true
        unsigned long startm = millis(); // 记录函数开始时的运行毫秒数
        unsigned long pass = 0; // 逝去的毫秒数
        do {
            delay(10);
            if (!Inquire()) {
                r = false;
                break;
            }
            // 过去的时间
            pass = mmhardware.TickPassed(startm, millis());
        } while (pass < ms);
        return r;
    }

    // 返回初始位置，实现InquireDelay的方法
    // 注意这里只是将下一个菜单项设置为返回，需要功能自行退出
    virtual void GoHome()
    {
        this->NextMenuCate = 0; // 返回0分类的0项
        this->NextMenuItem = 0;
    }

    uint16_t ExecMenu(uint8_t CateID, uint8_t ItemID)
    {
        return this->mmm.ExecItem(CateID, ItemID, this);
    }

    // 主循环
    // 左右选择大项,数字键用来选择子项目,一个大项目下面最多包含10个子项目
    void MainLoop();

    // 执行初始化
    bool Init()
    {
        pinMode(PIN_BUZZER, OUTPUT); // 设置蜂鸣器引脚
        mmhardware.Beep(true);
        uint16_t r = 0;
        UART_USB.begin(115200); // 打开串口通信
        UART_BLE.begin(9600); // 打开串口1，蓝牙蓝牙模块通信
        UART_BLE.print("AT+NAME=MagicMatrix\r\n"); // 设置蓝牙名称
        mmhardware.Init(); // 执行硬件初始化

        // 调用功能池初始化
        MMFPSetup();
        mmhardware.Beep(false);
        return r;
    }

} mmmain;

// 主循环
void MMMain::MainLoop()
{

    // for (;;) {
    //  如果下一个位菜单置存在则更新当前菜单位置，否则将下一位置改为当前位置
    if (mmm.ItemExists(this->NextMenuCate, this->NextMenuItem)) {
        this->CurrMenuCate = this->NextMenuCate;
        this->CurrMenuItem = this->NextMenuItem;
        this->ExecMenu(this->CurrMenuCate, this->CurrMenuItem); // 循环执行当前菜单功能
    } else {
        this->NextMenuCate = this->CurrMenuCate;
        this->NextMenuItem = this->CurrMenuItem;
    }
    this->Inquire();
    //}
}

#endif