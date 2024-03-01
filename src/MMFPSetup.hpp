/*
 * @File :  MMFPSetup.hpp
 * @Time :  2024/02/15 01:31:56
 * @Auth :
 * @Vers :  1.0
 * @Desc :  功能池初始化
 */

#ifndef _MMFPSETUP_HPP
#define _MMFPSETUP_HPP

#include "MMDefine.hpp"

#include "MMFunc/MMFuncPool.hpp"
#include "MMFunc/MMF_MatrixTest.hpp"
#include "MMFunc/MMF_DispTime_1.hpp"
#include "MMFunc/MMF_DispDate_1.hpp"
#include "MMFunc/MMF_DispDHT_1.hpp"
#include "MMFunc/MMF_DispBmpLoop.hpp"
#include "MMFunc/MMF_FillRainbow.hpp"
#include "MMFunc/MMF_ScoreBoard.hpp"


// 定义功能类型,为后期扩展作准备,目前默认只有0
#define MMF_TYPE_0 (0x00)

// 定义矩阵测试功能
#define MMF_ID_MATRIXTEST (0x0000)
MMF_MatrixTest mmf_matrixtest(MMF_ID_MATRIXTEST);

// 显示时间
#define MMF_ID_DISPTIME_1 (0x0001)
MMF_DispTime_1 mmf_disptime_1(MMF_ID_DISPTIME_1);

// 显示日期
#define MMF_ID_DISPDATE_1 (0x0002)
MMF_DispDate_1 mmf_dispdate_1(MMF_ID_DISPDATE_1);

// 显示温湿度
#define MMF_ID_DISPDHT_1 (0x0003)
MMF_DispDHT_1 mmf_dispdht_1(MMF_ID_DISPDHT_1);

// 循环显示图片
#define MMF_ID_DISPBMPLOOP (0x0004)
MMF_DispBmpLoop mmf_dispbmploop(MMF_ID_DISPBMPLOOP);

// 彩虹填充
#define MMF_ID_FILLRAINBOW (0x0005)
MMF_FillRainbow mmf_fillrainbow(MMF_ID_FILLRAINBOW);

// 记分牌
#define MMF_ID_SCOREBOARD (0x0006)
MMF_ScoreBoard mmf_scoreboard(MMF_ID_SCOREBOARD);
// 将功能模块加入功能池
void MMFPSetup()
{
    mmfuncpool.Append(&mmf_matrixtest);
    mmfuncpool.Append(&mmf_disptime_1);
    mmfuncpool.Append(&mmf_dispdate_1);    
    mmfuncpool.Append(&mmf_dispdht_1);    
    mmfuncpool.Append(&mmf_dispbmploop);    
    mmfuncpool.Append(&mmf_fillrainbow);    
    mmfuncpool.Append(&mmf_scoreboard);
    
}

#endif