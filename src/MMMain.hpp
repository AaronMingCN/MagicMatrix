/**
 * @file MMMain.hpp
 * @date 2024/02/20 16:10:24
 * @author  
 * @version 1.0
 * @brief 主程序类
 * @details
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
#include <Scheduler.h>

/// @brief MagicMatrix 主程序类
class MMMain : InquireDelay {

public:
    /// @brief 构造
    MMMain() {};
    // 析构
    // ~MMMain() {    };

    /// @brief 更新最后检测到人体时间
    void UpdatePIRR()
    {
        if (mmhardware.GetPIRR()) {
            mmscr.RenewPIRR();
            // UART_USB.println("Got");
        }
    }

    /// @brief 根据人体检测设置亮度
    void CheckPIRR()
    {
        this->UpdatePIRR(); // 如果检测到人，记录当前上电时间
        mmscr.UpdateBrightness(); // 更新屏幕亮度
    }

    /// @brief 将红外线收到的按键值转换为数值
    /// @param IRRCode
    /// @return 对应整数，转换失败返回-1
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

    /// @brief 接收并设置当前菜单位置
    /// @param[out] IRRCode 返回红外线值
    /// @return 是否切换了菜单位置
    bool IRRSetMenu(uint16_t& IRRCode)
    {
        bool r = false;
        IRRCode = IRK_NONE;
        if (mmhardware.IRRCode(IRRCode)) {
            mmscr.RenewPIRR(); // 刷新检测到人体的时间
            mmscr.UpdateBrightness(); // 更新当前亮度

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

    /// @brief 处理串口信息
    /// @param[in] uart 串口
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

    /// @brief 实现InquireDelay方法
    /// @param[out] IRRCode 读取到的红外线编码
    /// @return 询问结果
    virtual bool Inquire(uint16_t& IRRCode)
    {
        this->ProcUART(UART_USB); // 处理USB串口
        this->ProcUART(UART_BLE); // 处理BLE串口

        // this->CheckPIRR(); // 由于功能块内部需要调用红外线数据，取消此部分多线程处理
        this->IRRSetMenu(IRRCode);
        Scheduler.yield(); // 释放资源
        return (mmmenu.NextMenuItem == mmmenu.CurrMenuItem && mmmenu.NextMenuCate == mmmenu.CurrMenuCate);
    }

    /// @brief 实现InquireDelay方法
    virtual bool Inquire()
    {
        uint16_t IRRCode;
        return Inquire(IRRCode);
    }

    /// @brief 实现IDelay方法
    /// @param ms 等待时间
    /// @param[out] IRRCode 读取到的红外编码
    /// @param ReturnWhenDecode 当读取到红外编码是否立刻返回，默认false
    /// @return 询问结果
    virtual bool IDelay(unsigned long ms, uint16_t& IRRCode, bool ReturnWhenDecode = false)
    {
        bool r = true; // 默认结果为true
        unsigned long startm = millis(); // 记录函数开始时的运行毫秒数
        unsigned long pass = 0; // 逝去的毫秒数
        IRRCode = IRK_NONE;
        do {
            delay(10);
            if (!Inquire(IRRCode)) {
                r = false;
                break;
            }
            if (IRRCode && ReturnWhenDecode)
                break;
            // 过去的时间
            pass = mmhardware.TickPassed(startm, millis());
        } while (pass < ms);
        return r;
    }

    /// @brief 实现IDelay方法
    /// @param ms 等待时间
    /// @return 询问结果
    virtual bool IDelay(unsigned long ms)
    {
        uint16_t IRRCode;
        return this->IDelay(ms, IRRCode);
    }

    /// @brief 执行菜单项
    /// @param CateID 分类ID
    /// @param ItemID 项目ID
    /// @return 执行结果
    uint16_t ExecMenu(uint8_t CateID, uint8_t ItemID)
    {
        return mmmenu.ExecItem(CateID, ItemID, this);
    }

    /// @brief 主循环
    void MainLoop()
    {
        mmhardware.BeepDelay(20);
        for (;;) {
            // 切换菜单
            mmmenu.Switch(this);
            this->Inquire();
        }
    }

    /// @brief 设置蓝牙名称
    void SetBLEName()
    {
        // UART_BLE.print("AT+NAME=MagicMatrix\r\n"); // 设置蓝牙名称
        UART_BLE.print("AT+MAC?\r\n"); // 先获得蓝牙的硬件地址
        String s = UART_BLE.readString();
        UART_USB.println(s.substring(13));
        // 将蓝牙的硬件地址追加并修改该蓝牙名称
        UART_BLE.print("AT+NAME=MagicMatrix_" + s.substring(13) + "\r\n");
        UART_USB.println(UART_BLE.readString());
    }

    /// @brief 读取设置项目
    bool LoadCfg()
    {
        bool r = mmconfig.Load(); // 读取配置信息
        if (r) {
            // 将当前设置菜单项读取
            mmmenu.NextMenuCate = mmconfig.Config[CFG_MENUCATE];
            mmmenu.NextMenuItem = mmconfig.Config[CFG_MENUITEM];
            // 读取当前循环静态图片的序号
            mmf_dispbmpstatic.NextOrder = mmconfig.Config[CFG_DISPBMPIDX];
            mmf_dispbmpstatic.CurrOrder = mmconfig.Config[CFG_DISPBMPIDX];
        }
        return r;
    }

    /// @brief 执行初始化
    /// @return 执行结果
    bool Init()
    {
        pinMode(PIN_BUZZER, OUTPUT); // 设置蜂鸣器引脚
        mmhardware.BeepDelay(20);
        uint16_t r = 0;
        UART_USB.begin(115200); // 打开串口通信
        // UART_USB.setTimeout(10); // 设置串口读取超时
        UART_BLE.begin(9600); // 打开串口1，蓝牙蓝牙模块通信
        UART_BLE.setTimeout(100);
        // while(!UART_BLE);
        this->SetBLEName();
        mmhardware.Init(); // 执行硬件初始化
        this->LoadCfg();
        // 调用功能池初始化
        MMFPSetup();

        return r;
    }

} mmmain;

#endif