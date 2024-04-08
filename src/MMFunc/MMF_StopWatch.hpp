/**
 * @file MMF_Stopwatch.hpp
 * @date 2024/04/08 18:38:23
 * @author 
 * @version 1.0
 * @brief 计时器
 * @details 计时器模块，用于统计消耗的时间
 */


#ifndef _MMF_STOPWATCH_HPP
#define _MMF_STOPWATCH_HPP

#include "../MMFill.hpp"
#include "MMFunc.hpp"
#include "MMScr.hpp"

/// @brief 计时器功能模块类
class MMF_StopWatch : public MMFunc {
public:
    /// @brief 构造函数
    /// @param fid 当前功能ID
    MMF_StopWatch(uint16_t fid)
        : MMFunc(fid)
    {
        
    }

    

    /// @brief 执行功能
    /// @param IDelay 询问等待接口
    /// @return 执行结果    
    virtual MMFExecR_t Exec(InquireDelay* IDelay)
    {
        if (IDelay->Inquire()) {
            mmscr.FillAll(255, 0, 0);
            mmscr.Update();
            if (IDelay->IDelay(500)) {
                mmscr.FillAll(0, 255, 0);
                mmscr.Update();
            }
            if (IDelay->IDelay(500)) {
                mmscr.FillAll(0, 0, 255);
                mmscr.Update();
            }
            if (IDelay->IDelay(500)) {
                mmscr.SetEmpty();
                mmscr.Update();
            }
        }
        return EXECR_OK;
    }
};


#endif