/*
 * @File :  MMMenu.hpp
 * @Time :  2024/02/20 13:23:22
 * @Auth :
 * @Vers :  1.0
 * @Desc :  菜单相关的内容和操作
 */

#ifndef _MMMENU_HPP
#define _MMMENU_HPP

#include <vector>
// 引用功能池初始化头，用于将菜单条目绑定到功能
#include "MMFPSetup.hpp"
#include "MMDefine.hpp"

// 考虑到系统的功能层级简单,不采用树形菜单结构,这里采用单层菜单分类加菜单项的方法
// 菜单分类ID和菜单项ID都是8位无符号数,共可表示256 * 256个项目

// 菜单条目的结构体

/// @brief 菜单条目
struct MMMenuItem {
    /// @brief 所属的分类ID
    uint8_t CateID;
    /// @brief 条目ID
    uint8_t ItemID; 
    /// @brief 对应的功能ID
    uint16_t FuncID;
};

// 菜单类
class MMMenu {
public:
    uint8_t CurrMenuCate = 0; // 当前所在的菜单类
    uint8_t CurrMenuItem = 0; // 当前所在的菜单项目
    uint8_t NextMenuCate = 0; // 下一个菜单类
    uint8_t NextMenuItem = 0; // 下一个菜单位置


    /// @brief 菜单条目,菜单条目不进行重复检查，执行时只针对符合key值的第一条
    std::vector<MMMenuItem> Items;
    MMFuncPool *FPool; // 功能池

    /// @brief 构造函数
    /// @param fp : 根位置的Fid
    MMMenu(MMFuncPool *fp){
        this->FPool = fp;
        LoadItems();
    };

    // 返回最初位置
    void GoHome()
    {
        this->NextMenuCate = 0; // 返回0分类的0项
        this->NextMenuItem = 0;
    }

    // 执行条目对应功能
    MMFExecR_t ExecItem(uint8_t CateID, uint8_t ItemID, InquireDelay *IDelay) {
        MMFExecR_t r = EXECR_ERROR; // 定义菜单执行结果，默认为EXECR_ERROR
        for (auto it : Items) {
            if (it.CateID == CateID && it.ItemID == ItemID) { // 通过传入的菜单键值在条目列表中查找
                r = this->FPool->ExecFunc(it.FuncID, IDelay);
                break;
            }
        } 
        return r;
    }

    // 条目是否存在
    bool ItemExists(uint8_t CateID, uint8_t ItemID) {
        bool r = false;
        for (auto it : Items) {
            if (it.CateID == CateID && it.ItemID == ItemID) { // 通过传入的菜单键值在条目列表中查找
                r = true;
                break;
            }
        } 
        return r;
    }

    // 载入菜单项
    void LoadItems() {
        this->Items.clear();
        // 菜单分类0x00 
        this->Items.push_back({0x00, 0x00, MMF_ID_DISPTIME_1}); // 载入菜单功能 显示时间
        this->Items.push_back({0x00, 0x01, MMF_ID_DISPDATE_1}); // 载入菜单功能 显示日期
        this->Items.push_back({0x00, 0x02, MMF_ID_DISPDHT_1}); // 载入菜单功能 显示温湿度
        this->Items.push_back({0x00, 0x03, MMF_ID_COUNTDOWN}); // 倒计时
        this->Items.push_back({0x00, 0x09, MMF_ID_MATRIXTEST}); // 载入菜单功能 测试矩阵
        // 菜单分类0x01
        this->Items.push_back({0x01, 0x00, MMF_ID_DISPBMPLOOP});  // 循环显示位图
        // 菜单分类0x02
        this->Items.push_back({0x02, 0x00, MMF_ID_SCOREBOARD});  // 记分牌
        this->Items.push_back({0x02, 0x01, MMF_ID_DICE});  // 投骰子
        // 菜单分类0x03
        this->Items.push_back({0x03, 0x00, MMF_ID_FILLRAINBOW});  // 填充
    }

    // 切换位置
    bool Switch(InquireDelay *IDelay) {
        bool r = false;
        //  如果下一个位菜单置存在则更新当前菜单位置，否则将下一位置改为当前位置
        if (this->ItemExists(this->NextMenuCate, this->NextMenuItem)) {
            this->CurrMenuCate = this->NextMenuCate;
            this->CurrMenuItem = this->NextMenuItem;
            // 将当前菜单位置保存到Config
            mmconfig.Config[CFG_MENUCATE] = this->CurrMenuCate;
            mmconfig.Config[CFG_MENUITEM] = this->CurrMenuItem;
            mmconfig.NeedSave = true; // 标记配置文件需要保存
            // mmconfig.Save(); // 将当前配置保存，已经放在另外线程中处理
            this->ExecItem(this->CurrMenuCate, this->CurrMenuItem, IDelay); // 循环执行当前菜单功能
            r = true;
        } else {
            this->NextMenuCate = this->CurrMenuCate;
            this->NextMenuItem = this->CurrMenuItem;
        }
        return r;
    }


} mmmenu(&mmfuncpool);

#endif