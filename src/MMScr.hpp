/**
 * @file MMScr.hpp
 * @date 2024/02/13 10:33:34
 * @author Aaron Ming
 * @version 1.0
 * @brief 矩阵屏幕功能相关封装
 * @details 将矩阵屏幕相关的功能进行封装
 */

#ifndef _MMSCR_HPP
#define _MMSCR_HPP

#include "MMDefine.hpp"
#include "MMHardware.hpp"
#include "MMRamBmp.hpp"

/// @brief 矩阵屏幕类
class MMScr {
public:
    unsigned long LastPIRR = 0; ///< 最后检测到人体的时间
    uint8_t CurrBright = M_BRIGHT; ///< 当前亮度，避免重复刷新
    uint8_t NextBright = M_BRIGHT; ///< 下一个亮度

    /// @brief 清空屏幕
    /// @note 需要手动重新绘制屏幕
    void SetEmpty()
    {
        mmhardware.matrix.clear();
    }

    /// @brief 更新矩阵重新绘制
    void Update()
    {
        mmhardware.matrix.show();
        while (!mmhardware.matrix.canShow())
            ; // 等待绘图结束
    }

    // 清空矩阵，并立刻显示
    void Clear()
    {
        SetEmpty();
        Update();
    }

    // 设置一个像素的颜色
    void SetPixel(uint16_t x, uint16_t y, uint8_t R, uint8_t G, uint8_t B)
    {
        mmhardware.matrix.drawPixel(x, y, mmhardware.matrix.Color(R, G, B));
    }

    // 填充整个屏幕
    void Fill(uint8_t R, uint8_t G, uint8_t B)
    {
        for (uint8_t r = 0; r < M_HEIGHT; ++r) { // 将所有颜色清空
            for (uint8_t c = 0; c < M_WIDTH; ++c) {
                mmhardware.matrix.drawPixel(c, r, mmhardware.matrix.Color(R, G, B));
            }
        }
    }

    // 将RamBmp绘制到屏幕
    void DrawRamBmp(MMRamBmp& rb)
    {
        for (uint8_t r = 0; r < M_HEIGHT; ++r) { // 将所有颜色清空
            for (uint8_t c = 0; c < M_WIDTH; ++c) {
                RGB t;
                rb.GetPixel(c, r, t); // 定义临时像素并从RamBmp读取
                mmhardware.matrix.drawPixel(c, r, t.Color()); // 将像素绘制到矩阵屏幕
            }
        }
    }

    // 更新显示屏亮度
    void UpdateBrightness()
    {
        // 获取距离上次点亮屏幕的时间
        unsigned long pass = mmhardware.TickPassed(this->LastPIRR, millis());
        // 根据检测到人体的情况修改屏幕亮度
        if (pass < M_PIRR_DELAY) {
            this->NextBright = M_BRIGHT;
        } else {
            this->NextBright = M_BIRGHT_STANDBY;
        }
        // 如果需要改变亮度则更改并刷新
        if (this->NextBright != this->CurrBright) {
            this->CurrBright = this->NextBright;
            mmhardware.matrix.setBrightness(this->CurrBright);
            mmhardware.matrix.show();
        }
    }

    // 设置最后检测到时间
    void RenewPIRR()
    {
        this->LastPIRR = millis();
    }

} mmscr;

#endif