/*
 * @File :  RamBmp.hpp
 * @Time :  2024/02/13 10:30:27
 * @Vers :  1.0
 * @Desc :  内存bmp位图,将位图文件保存在ram中
 */
#ifndef _MMRAMBMP_HPP
#define _MMRAMBMP_HPP

#include "MMDefine.hpp"

// 内存bmp图片
class MMRamBmp {
public:
    uint16_t width = 0;
    uint16_t height = 0;

    RGB* bmp = NULL; // 定义一个RGB数组
    // 构造函数
    MMRamBmp(uint16_t Width = M_WIDTH, uint16_t Height = M_HEIGHT)
    {
        this->width = Width;
        this->height = Height;
        this->bmp = new RGB[Width * Height]; // 根据宽和高创建RGB数组
        this->Clear();
    };

    // 析构函数
    ~MMRamBmp()
    {
        delete[] bmp; // 析构释放RBG数组
    };

    // 清空所有像素
    void Clear()
    {
        memset(bmp, 0, height * width * (sizeof(RGB)));
    }

    // 获得RGB值设置像素
    void GetPixel(uint16_t x, uint16_t y, RGB& Pix)
    {
        Pix = this->bmp[y * width + x];
    }

    // 根据设置像素RGB值
    void SetPixel(uint16_t x, uint16_t y, uint8_t R, uint8_t G, uint8_t B)
    {
        RGB &pix = this->bmp[y * width + x];
        pix.R = R;
        pix.G = G;
        pix.B = B;
    }

    // 根据RGB结构设置
    void SetPixel(uint16_t x, uint16_t y, RGB& Pix)
    {
        this->SetPixel(x, y, Pix.R, Pix.G, Pix.B);
    }
};

#endif