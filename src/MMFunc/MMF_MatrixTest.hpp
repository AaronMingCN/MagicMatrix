/*
 * @File :  MMF_MatrixTest.hpp
 * @Time :  2024/02/15 00:56:25
 * @Auth :  
 * @Vers :  1.0
 * @Desc :  矩阵屏幕测试功能块
 */

#ifndef _MMF_MATRIXTEST_HPP
#define _MMF_MATRIXTEST_HPP

#include "MMFunc.hpp"
#include "../MMFill.hpp"

// 矩阵屏幕测试类，测试RGB显示
class MMF_MatrixTest: public MMFunc {
public:
    MMF_MatrixTest(uint16_t fid): MMFunc(fid) {}
    virtual uint16_t Exec() {
        mmfill.MatrixTest();
        return EXECR_OK;
    }
};

#endif