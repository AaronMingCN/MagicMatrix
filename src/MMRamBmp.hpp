/**
 * @file MMRamBmp.hpp
 * @date 2024/02/13 10:30:27
 * @author  
 * @version 1.0
 * @brief 内存bmp位图,将位图文件保存在ram中
 */

#ifndef _MMRAMBMP_HPP
#define _MMRAMBMP_HPP

#include "MMCanvas.hpp"
#include "MMDefine.hpp"

/// @brief 内存图片类
class MMRamBmp : public MMCanvas {
public:
    uint16_t width = 0; ///< 宽度
    uint16_t height = 0; ///< 高度

    RGB* bmp = NULL; ///< 定义一个RGB数组

    /// @brief 构造函数
    /// @param Width 高度
    /// @param Height 宽度
    MMRamBmp(uint16_t Width = M_WIDTH, uint16_t Height = M_HEIGHT)
    {
        this->width = Width;
        this->height = Height;
        this->bmp = new RGB[Width * Height]; // 根据宽和高创建RGB数组
        this->SetEmpty();
    };

    /// @brief 析构函数
    ~MMRamBmp()
    {
        delete[] bmp; // 析构释放RBG数组
    };

    /// @brief 清空所有像素
    /// @note 覆盖父类方法
    virtual void SetEmpty()
    {
        memset(bmp, 0, height * width * (sizeof(RGB)));
    }

    /// @brief 获得RGB值设置像素
    /// @param x 横坐标
    /// @param y 纵坐标
    /// @param[out] Pix 返回的像素rgb
    /// @return 获取结果
    bool GetPixel(int16_t x, int16_t y, RGB& Pix)
    {
        bool r = false;
        if (x >= 0 && x < this->width && y >= 0 && y < this->height) { // 边界检查
            Pix = this->bmp[y * width + x];
            r = true;
        }
        return r;
    }

    /// @brief 设置一个像素点
    /// @param x 横坐标
    /// @param y 纵坐标
    /// @param R 红色值
    /// @param G 绿色值
    /// @param B 蓝色值
    /// @note 实现MMCanvas方法
    virtual void SetPixel(int16_t x, int16_t y, uint8_t R, uint8_t G, uint8_t B)
    {
        if (x >= 0 && x < this->width && y >= 0 && y < this->height) { // 边界检查
            RGB& pix = this->bmp[y * width + x];
            pix.R = R;
            pix.G = G;
            pix.B = B;
        }
    }
};

#endif