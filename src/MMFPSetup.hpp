/**
 * @file MMFPSetup.hpp
 * @date 2024/02/15 01:31:56
 * @author 
 * @version 1.0
 * @brief 功能池初始化
 * @details 将所有功能块集中创建初始化，并放入功能池中
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
#include "MMFunc/MMF_Dice.hpp"
#include "MMFunc/MMF_CountDown.hpp"


/// @brief 定义功能类型,为后期扩展作准备,目前默认只有0
#define MMF_TYPE_0 (0x00)

/// @brief 定义矩阵测试功能
#define MMF_ID_MATRIXTEST (0x0000)
MMF_MatrixTest mmf_matrixtest(MMF_ID_MATRIXTEST);

/// @brief 显示时间
#define MMF_ID_DISPTIME_1 (0x0001)
MMF_DispTime_1 mmf_disptime_1(MMF_ID_DISPTIME_1);

/// @brief 显示日期
#define MMF_ID_DISPDATE_1 (0x0002)
MMF_DispDate_1 mmf_dispdate_1(MMF_ID_DISPDATE_1);

/// @brief 显示温湿度
#define MMF_ID_DISPDHT_1 (0x0003)
MMF_DispDHT_1 mmf_dispdht_1(MMF_ID_DISPDHT_1);

/// @brief 循环显示图片
#define MMF_ID_DISPBMPLOOP (0x0004)
MMF_DispBmpLoop mmf_dispbmploop(MMF_ID_DISPBMPLOOP);

/// @brief 彩虹填充
#define MMF_ID_FILLRAINBOW (0x0005)
MMF_FillRainbow mmf_fillrainbow(MMF_ID_FILLRAINBOW);

/// @brief 记分牌
#define MMF_ID_SCOREBOARD (0x0006)
MMF_ScoreBoard mmf_scoreboard(MMF_ID_SCOREBOARD);

/// @brief 投骰子
#define MMF_ID_DICE (0x0007)
MMF_Dice mmf_dice(MMF_ID_DICE);

/// @brief 倒计时
#define MMF_ID_COUNTDOWN (0x0008)
MMF_CountDown mmf_countdown(MMF_ID_COUNTDOWN);

/// @brief 倒计时

/// @brief 将功能模块加入功能池
void MMFPSetup()
{
    mmfuncpool.Clear();
    mmfuncpool.Append(&mmf_matrixtest);
    mmfuncpool.Append(&mmf_disptime_1);
    mmfuncpool.Append(&mmf_dispdate_1);    
    mmfuncpool.Append(&mmf_dispdht_1);    
    mmfuncpool.Append(&mmf_dispbmploop);    
    mmfuncpool.Append(&mmf_fillrainbow);    
    mmfuncpool.Append(&mmf_scoreboard);
    mmfuncpool.Append(&mmf_dice);
    mmfuncpool.Append(&mmf_countdown);
}

#endif