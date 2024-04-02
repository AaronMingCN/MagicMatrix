/**
 * @file MMF_DispDateTime.hpp
 * @date 2024/04/03 00:03:32
 * @author Aaron Ming 
 * @version 1.0
 * @brief 显示日期时间
 * @details 同时显示日期时间
 */

#ifndef _MMF_DISPDATETIME_HPP
#define _MMF_DISPDATETIME_HPP

#include "../MMFill.hpp"
#include "MMFunc.hpp"
#include "MMScr.hpp"


/// @brief 显示日期时间
class MMF_DispDateTime : public MMFunc {
public:
    /// @brief 构造函数
    /// @param fid 当前功能ID
    MMF_DispDateTime(uint16_t fid)
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
