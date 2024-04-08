/**
 * @file MMCanvas.hpp
 * @date 2024/03/27 06:17:26
 * @author  
 * @version 1.0
 * @brief 画布接口
 * @details 实现画布接口用于在不同的设备绘图，内存或矩阵屏
 */

#ifndef _MMCANVAS_HPP
#define _MMCANVAS_HPP

/// @brief 画布类
/// @details 实现画布功能相关的接口，由子类实现
class MMCanvas {
public:
    /// @brief 设置一个像素点
    /// @param x 横坐标
    /// @param y 纵坐标
    /// @param R 红色值
    /// @param G 绿色值
    /// @param B 蓝色值
    /// @note 此方法需要子类实现
    virtual void SetPixel(int16_t x, int16_t y, uint8_t R, uint8_t G, uint8_t B) = 0;

    /// @brief 设置一个像素点
    /// @param x 横坐标
    /// @param y 纵坐标
    /// @param rgb RGB结构体
    virtual void SetPixel(int16_t x, int16_t y, RGB rgb)
    {
        this->SetPixel(x, y, rgb.R, rgb.G, rgb.B);
    }

    /// @brief 填充所有
    /// @param R 红色值
    /// @param G 绿色值
    /// @param B 蓝色值
    // 填充整个屏幕
    void FillAll(uint8_t R, uint8_t G, uint8_t B)
    {
        for (int16_t y = 0; y < M_HEIGHT; ++y) { // 将所有颜色清空
            for (int16_t x = 0; x < M_WIDTH; ++x) {
                this->SetPixel(x, y, R, G, B);
            }
        }
    }

    /// @brief 清空屏幕
    /// @note 需要手动重新绘制屏幕
    virtual void SetEmpty()
    {
        this->FillAll(0, 0, 0);
    }
};

#endif
