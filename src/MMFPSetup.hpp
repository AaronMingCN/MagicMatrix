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

#include "MMFunc/MMF_CountDown.hpp"
#include "MMFunc/MMF_Dice.hpp"
#include "MMFunc/MMF_DispBmpLoop.hpp"
#include "MMFunc/MMF_DispDHT_1.hpp"
#include "MMFunc/MMF_DispDate_1.hpp"
#include "MMFunc/MMF_DispTime_1.hpp"
#include "MMFunc/MMF_FillRainbow.hpp"
#include "MMFunc/MMF_MatrixTest.hpp"
#include "MMFunc/MMF_ScoreBoard.hpp"
#include "MMFunc/MMFuncPool.hpp"

/// 定义功能类型,为后期扩展作准备,目前默认只有0
#define MMF_TYPE_0 (0x00)

#define MMF_ID_MATRIXTEST (0x0000) ///< 矩阵测试功能块ID
MMF_MatrixTest mmf_matrixtest(MMF_ID_MATRIXTEST); ///< 矩阵功能块实例

#define MMF_ID_DISPTIME_1 (0x0001) ///< 显示时间功能块ID
MMF_DispTime_1 mmf_disptime_1(MMF_ID_DISPTIME_1); ///< 显示时间功能块实例

#define MMF_ID_DISPDATE_1 (0x0002) ///< 显示日期功能块ID
MMF_DispDate_1 mmf_dispdate_1(MMF_ID_DISPDATE_1); ///< 显示日期功能块实例

#define MMF_ID_DISPDHT_1 (0x0003) ///< 显示温湿度功能块ID
MMF_DispDHT_1 mmf_dispdht_1(MMF_ID_DISPDHT_1); ///< 显示温湿度功能块实例

#define MMF_ID_DISPBMPLOOP (0x0004) ///< 循环显示图片功能块ID
MMF_DispBmpLoop mmf_dispbmploop(MMF_ID_DISPBMPLOOP); ///< 循环显示图片功能实例

#define MMF_ID_FILLRAINBOW (0x0005) ///< 彩虹填充功能块ID
MMF_FillRainbow mmf_fillrainbow(MMF_ID_FILLRAINBOW); ///< 彩虹填充功能块实例

#define MMF_ID_SCOREBOARD (0x0006) ///< 记分牌功能块ID
MMF_ScoreBoard mmf_scoreboard(MMF_ID_SCOREBOARD); ///< 记分牌功能块实例

#define MMF_ID_DICE (0x0007) ///< 投骰子功能块ID
MMF_Dice mmf_dice(MMF_ID_DICE); ///< 投骰子功能块实例

#define MMF_ID_COUNTDOWN (0x0008) ///< 倒计时功能块ID
MMF_CountDown mmf_countdown(MMF_ID_COUNTDOWN); ///< 倒计时功能块实例

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