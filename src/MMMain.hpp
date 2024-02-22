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
    // MMMenu menu;
    static uint8_t CurrMenuCate; // 当前所在的菜单位置
    // MMMenu menu;
    static uint8_t CurrMenuItem; // 当前所在的菜单位置

    // 定义菜单
    MMMenu mmm;

    // 构造
    MMMain()
        : mmm(mmfuncpool) {

        };
    // 析构
    ~MMMain() {

    };

    // 实现InquireDelay方法
    virtual bool Inquire()
    {
        return true;
    }
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
            if (nowm > startm) pass = (nowm - startm); // 如果没有出现环绕
            else pass = (mxlong - startm) + nowm; // 如果出现环绕
        } while (pass < ms);
        return r;
    }

    // 主循环
    // 左右选择大项,数字键用来选择子项目,一个大项目下面最多包含10个子项目
    void MainLoop();

    // 执行初始化
    bool Init()
    {
        uint16_t r = 0;
        Serial.begin(19200); // 打开串口通信

        mmhardware.Init(); // 执行硬件初始化

        // 调用功能池初始化
        MMFPSetup();
        // 执行功能池中的矩阵测试功能
        // mmfuncpool.ExecFunc(MMF_ID_MATRIXTEST);
        // 执行当前菜单
        return r;
    }

} mmmain;

// 主循环
// 左右选择大项,数字键用来选择子项目,一个大项目下面最多包含10个子项目
void MMMain::MainLoop()
{
    this->mmm.ExecItem(0, 0, this);
}

#endif