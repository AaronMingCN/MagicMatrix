/*
 * @File :  MMFuncPool.hpp
 * @Time :  2024/02/14 22:50:10
 * @Auth :
 * @Vers :  1.0
 * @Desc :  功能池，用于集中管理和调用功能块
 */

#ifndef _MMFUNCPOOL_HPP
#define _MMFUNCPOOL_HPP

#include "MMFunc/MMFunc.hpp"
#include <vector>

// MMFuncPool功能池
class MMFuncPool {
private:
    // 功能块列表
    std::vector<MMFunc *> items;
public:
    // MMFuncPool();
    // 析构,释放功能列表
    ~MMFuncPool() {
        this->items.clear();
    };

    // 清空功能池
    void Clear() {
        this->items.clear();
    }
    // 将功能块加入到池中
    void Append(MMFunc *mmf)
    {
        mmf->FPool = this;
        this->items.push_back(mmf);
    }

    // 根据功能块FID执行对应的功能
    uint16_t ExecFunc(uint16_t fid, InquireDelay *IDelay)
    {
        uint16_t r = EXECR_ERROR; // 定义返回结果,默认为错误
        for (auto i : items) {
            if (i->FID == fid) {
                r = i->Exec(IDelay);
                break;
            }
        }
        return r;
    }
} mmfuncpool;

#endif