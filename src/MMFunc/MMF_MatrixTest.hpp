/**
 * @file MMF_MatrixTest.hpp
 * @date 22024/02/15 00:56:25
 * @author Aaron Ming
 * @version 1.0
 * @brief 矩阵屏幕测试功能块
 * @details
 */

#ifndef _MMF_MATRIXTEST_HPP
#define _MMF_MATRIXTEST_HPP

#include "../MMFill.hpp"
#include "MMFunc.hpp"
#include "MMScr.hpp"

/// @brief 矩阵屏幕测试类，测试RGB显示
class MMF_MatrixTest : public MMFunc {
public:
    /// @brief 构造函数
    /// @param fid 当前功能ID
    MMF_MatrixTest(uint16_t fid)
        : MMFunc(fid)
    {
        
    }

    /// @brief 执行功能
    /// @param IDelay 询问等待接口
    /// @return 执行结果    
    virtual MMFExecR_t Exec(InquireDelay* IDelay)
    {
        if (IDelay->Inquire()) {
            mmscr.Fill(255, 0, 0);
            mmscr.Update();
            if (IDelay->IDelay(500)) {
                mmscr.Fill(0, 255, 0);
                mmscr.Update();
            }
            if (IDelay->IDelay(500)) {
                mmscr.Fill(0, 0, 255);
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