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

// 定义菜单Key的类型，键值每层采用无符号8位数每层可以有0~255个子项
typedef  std::vector<uint8_t> MMMenuItem_Key;

// 定义菜单条目的结构体
struct MMMenuItem {
    MMMenuItem_Key Key; // 键
    uint8_t FID; // 对应的功能ID
};

// 菜单类
class MMMenu {
public:
    // 菜单条目,菜单条目不进行重复检查，执行时只针对符合key值的第一条
    std::vector<MMMenuItem> Items;
    MMFuncPool *FPool; // 功能池
    MMFID_t RootFuncID; // 根位置执行的功能id
    // 构造，根位置的Fid
    MMMenu(MMFuncPool &fp, MMFExecR_t RootFID = MMF_ID_DISPTIME_1){
        FPool = &fp;
        RootFuncID = RootFID;
    };

    MMFExecR_t ExecItem(MMMenuItem_Key &Key) {
        MMFExecR_t r = EXECR_ERROR; // 定义菜单执行结果，默认为EXECR_ERROR
        for (auto it : Items) {
            if (it.Key == Key) { // 通过传入的菜单键值在条目列表中查找
                r = this->FPool->ExecFunc(it.FID);
                break;
            }
        } 
        return r;
    }
} mmmenu(mmfuncpool);

#endif