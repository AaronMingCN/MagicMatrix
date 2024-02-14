/*
 * @File :  MMFPSetup.hpp
 * @Time :  2024/02/15 01:31:56
 * @Auth :   
 * @Vers :  1.0
 * @Desc :  功能池初始化
 */

#ifndef _MMFPSETUP_HPP
#define _MMFPSETUP_HPP

// #include "MMFunc/MMFunc.hpp"
#include "MMFunc/MMFuncPool.hpp"


#include "MMFunc/MMF_MatrixTest.hpp"

// 定义功能池
MMFuncPool FPool;

// 定义功能类型,为后期扩展作准备,目前默认只有0
#define MMF_TYPE_0 (0x00) 

// 定义矩阵测试功能
#define MMF_ID_MATRIXTEST (0x0001)
MMF_MatrixTest mmf_matrixtest(MMF_ID_MATRIXTEST);

void MMFPSetup() {
    FPool.Append(&mmf_matrixtest);
}

#endif