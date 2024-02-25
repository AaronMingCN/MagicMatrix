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

// MagicMatrix 主程序类
class MMMain : InquireDelay {
public:
    uint8_t CurrMenuCate; // 当前所在的菜单位置
    uint8_t CurrMenuItem; // 当前所在的菜单位置
    uint8_t NextMenuItem; // 下一个菜单位置

    // 定义菜单
    MMMenu mmm;

    // 构造
    MMMain()
        : mmm(&mmfuncpool) {

        };
    // 析构
    ~MMMain() {

    };

    // 将红外线收到的按键值转换为数值
    int IRRVal()
    {
        int r = -1;
        switch (mmhardware.IRRCode()) {
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

    // 实现InquireDelay方法
    virtual bool Inquire()
    {
        int t = this->IRRVal(); // 读取红外数值
        // Serial.println(String(CurrMenuItem) + " " + String(NextMenuItem));
        while (Serial1.available()) {
            // String s = Serial1.readString();
            
            Serial.print(char(Serial1.read()));
        }
        if (t >= 0)
            NextMenuItem = t;
        return NextMenuItem == CurrMenuItem;
    }

    // 实现IDelay方法
    virtual bool IDelay(unsigned long ms)
    {
        unsigned long mxlong = (0 - 1); // unsigned long 的最大值,用户环绕计算

        bool r = true; // 默认结果为true
        unsigned long startm = millis(); // 记录函数开始时的运行毫秒数
        unsigned long nowm = 0; //
        unsigned long pass = 0; // 逝去的毫秒数
        do {
            delay(10);
            if (!Inquire()) {
                r = false;
                break;
            }
            nowm = millis(); // 记录当前毫秒数
            if (nowm > startm)
                pass = (nowm - startm); // 如果没有出现环绕
            else
                pass = (mxlong - startm) + nowm; // 如果出现环绕
        } while (pass < ms);
        return r;
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

        uint16_t r = 0;
        Serial.begin(9600); // 打开串口通信
        Serial1.begin(9600); // 打开串口1，蓝牙蓝牙模块通信
        Serial1.println("AT+NAME=MagicMatrix"); // 设置蓝牙名称
        mmhardware.Init(); // 执行硬件初始化
        mmhardware.Beep(true);
        delay(100);
        mmhardware.Beep(false);
        // 调用功能池初始化
        MMFPSetup();

        // 执行功能池中的矩阵测试功能
        // this->ExecMenu(0, 0);
        // 执行当前菜单
        return r;
    }

} mmmain;

// 主循环
void MMMain::MainLoop()
{
    for (;;) {
        if (mmm.ItemExists(this->CurrMenuCate, this->NextMenuItem)) {
            this->CurrMenuItem = this->NextMenuItem;
            this->ExecMenu(this->CurrMenuCate, this->CurrMenuItem); // 循环执行当前菜单功能
        } else
            NextMenuItem = CurrMenuItem;
        this->Inquire();
    }
}

#endif