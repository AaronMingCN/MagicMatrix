/**
 * @file MMScr.hpp
 * @date 2024/02/13 10:33:34
 * @author  
 * @version 1.0
 * @brief 矩阵屏幕功能相关封装
 * @details 将矩阵屏幕相关的功能进行封装
 */

#ifndef _MMSCR_HPP
#define _MMSCR_HPP

#include "MMCanvas.hpp"
#include "MMDefine.hpp"
#include "MMHardware.hpp"
#include "MMRamBmp.hpp"

/// @brief 矩阵屏幕类
class MMScr : public MMCanvas {
public:
    unsigned long LastPIRR = 0; ///< 最后检测到人体的时间
    uint8_t CurrBright = M_BRIGHT; ///< 当前亮度，避免重复刷新
    uint8_t NextBright = M_BRIGHT; ///< 下一个亮度

    /// @brief 将RGB转换为NeoPixel的颜色值
    /// @param R 红色值
    /// @param G 绿色值
    /// @param B 蓝色值
    /// @return NeoPixelColor
    uint16_t NeoColor(uint8_t R, uint8_t G, uint8_t B)
    {
        return mmhardware.matrix.Color(R, G, B);
    }

    /// @brief 将RGB转换为NeoPixel的颜色值
    /// @param rgb 颜色结构体
    /// @return NeoPixelColor
    uint16_t NeoColor(RGB rgb)
    {
        return this->NeoColor(rgb.R, rgb.G, rgb.B);
    }

    /// @brief 更新矩阵重新绘制
    void Update()
    {
        mmhardware.matrix.show();
        while (!mmhardware.matrix.canShow())
            ; // 等待绘图结束
    }

    /// @brief 清空矩阵，并立刻显示
    void Clear()
    {
        SetEmpty();
        Update();
    }

    /// @brief 设置一个像素点
    /// @param x 横坐标
    /// @param y 纵坐标
    /// @param R 红色值
    /// @param G 绿色值
    /// @param B 蓝色值
    /// @note 实现父类MMCanvas方法
    virtual void SetPixel(int16_t x, int16_t y, uint8_t R, uint8_t G, uint8_t B)
    {
        mmhardware.matrix.drawPixel(x, y, this->NeoColor(R, G, B));
    }

        /// @brief 将RamBmp绘制到屏幕
    /// @param rb 内存bmp
    void DrawRamBmp(MMRamBmp& rb)
    {
        for (uint8_t r = 0; r < M_HEIGHT; ++r) { // 将所有颜色清空
            for (uint8_t c = 0; c < M_WIDTH; ++c) {
                RGB t;
                rb.GetPixel(c, r, t); // 定义临时像素并从RamBmp读取
                // mmhardware.matrix.drawPixel(c, r, this->NeoColor(t));
                this->MMCanvas::SetPixel(c, r, t); // 将像素绘制到矩阵屏幕
            }
        }
    }

    /// @brief 更新显示屏亮度
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

    /// @brief 设置最后检测到时间
    void RenewPIRR()
    {
        this->LastPIRR = millis();
    }

} mmscr;

#endif