/*
 * @File :  MMFuncPool.h
 * @Time :  2024/02/14 22:50:10
 * @Auth :
 * @Vers :  1.0
 * @Desc :  功能池，用于集中管理和调用功能块
 */

#ifndef MMFUNCPOOL
#define MMFUNCPOOL

#include "MMFunc.h"
#include <vector>

class MMFuncPool {
private:
    std::vector<MMFunc*> items;

public:
    // MMFuncPool();
    // ~MMFuncPool();
    // 将功能块加入到池中
    void Append(MMFunc* mmf)
    {
        this->items.push_back(mmf);
    }

    // 根据功能块FID执行对应的功能
    uint16_t Exec(uint16_t fid)
    {
        for (auto i : items) {
            if (i->FID == fid) {
                return i->Exec();
            }
        }
        return EXECR_ERROR;
    }
};

#endif