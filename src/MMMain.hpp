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
#include "MMHardware.hpp"
#include "MMMenu.hpp"

// MagicMatrix 主程序类
class MMMain{
public:
    // MMMenu menu;
    MMMenuItem_Key CurrMenuKey; // 当前所在的菜单位置 
    // 构造
    MMMain() {

    };
    // 析构
    ~MMMain() {
        this->CurrMenuKey.clear(); // 情况当前所在的菜单位置
    };

    // 主循环
    void MainLoop() {

    }

    // 执行初始化
    bool Init() {
        uint16_t r = 0;
        Serial.begin(19200); // 打开串口通信

        mmhardware.Init(); // 执行硬件初始化

        // 调用功能池初始化
        MMFPSetup();
        // 执行功能池中的矩阵测试功能
        mmfuncpool.ExecFunc(MMF_ID_MATRIXTEST);     
        // 执行当前菜单
        mmmenu.ExecItem(this->CurrMenuKey);
        return r;  
    }

    // 返回上一级菜单
    void GoBack() {
        // 如果当前菜单Key非空则删除最后一个元素
        if (this->CurrMenuKey.size()) this->CurrMenuKey.pop_back();
        mmmenu.ExecItem(this->CurrMenuKey);
    }

    // 返回根菜单
    void GoHome() {
        // 清空菜单key
        this->CurrMenuKey.clear();
        mmmenu.ExecItem(this->CurrMenuKey);
    }
} mmmain;


#endif