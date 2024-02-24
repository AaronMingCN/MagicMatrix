/*
 * @File :  MMF_MatrixTest.hpp
 * @Time :  2024/02/15 00:56:25
 * @Auth :
 * @Vers :  1.0
 * @Desc :  矩阵屏幕测试功能块
 */

#ifndef _MMF_MATRIXTEST_HPP
#define _MMF_MATRIXTEST_HPP

#include "../MMFill.hpp"
#include "MMFunc.hpp"
#include "MMScr.hpp"

// 矩阵屏幕测试类，测试RGB显示
class MMF_MatrixTest : public MMFunc {
public:
    MMF_MatrixTest(uint16_t fid)
        : MMFunc(fid)
    {
        
    }
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