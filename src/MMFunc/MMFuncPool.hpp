/**
 * @file MMFuncPool.hpp
 * @date 2024/02/14 22:50:10
 * @author Aaron Ming
 * @version 1.0
 * @brief 功能池
 * @details 用于集中管理和调用功能块
 */

#ifndef _MMFUNCPOOL_HPP
#define _MMFUNCPOOL_HPP

#include "MMFunc/MMFunc.hpp"
#include <vector>

// MMFuncPool功能池

/// @brief 功能池类
/// @details 将功能块统一管理，提供统一的使用接口
class MMFuncPool {
private:
    /// @brief 功能块列表
    std::vector<MMFunc*> items;

public:
    // MMFuncPool();
    // 析构,释放功能列表

    /// @brief 析构
    /// @details 析构时清空功能池
    ~MMFuncPool()
    {
        this->items.clear();
    };

    /// @brief 清空功能池
    void Clear()
    {
        this->items.clear();
    }

    /// @brief 将功能块加入功能池
    /// @param mmf 功能块
    void Append(MMFunc* mmf)
    {
        mmf->FPool = this;
        this->items.push_back(mmf);
    }

    /// @brief 根据功能块ID执行对应功能
    /// @param fid 功能块ID
    /// @param IDelay 询问等待接口
    /// @return 功能块执行结果
    uint16_t ExecFunc(uint16_t fid, InquireDelay* IDelay)
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