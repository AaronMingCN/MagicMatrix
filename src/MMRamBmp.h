/*
 * @File :  RamBmp.h
 * @Time :  2024/02/13 10:30:27
 * @Vers :  1.0
 * @Desc :  内存bmp位图,将位图文件保存在ram中
 */
#ifndef _MMRAMBMP_H 
#define _MMRAMBMP_H 

#include "MMDefine.h"

// 内存bmp图片
class MMRamBmp{
public:
  uint16_t width = 0;
  uint16_t height = 0;
  
  RGB *bmp = NULL; // 定义一个RGB数组
  // 构造函数
  MMRamBmp(uint16_t Width = M_WIDTH, uint16_t Height = M_HEIGHT) {
    this->width = Width;
    this->height = Height;
    this->bmp = new RGB[Width * Height]; // 根据宽和高创建RGB数组
  };

  // 析构函数
  ~MMRamBmp() {
    delete[] bmp; // 析构释放RBG数组
  };

  // 获得RGB值设置像素
  void GetPixcel(uint16_t x, uint16_t y, RGB &Pix) {
    Pix = this->bmp[y * width + x];
  }

  // 根据设置像素RGB值
  void SetPixcel(uint16_t x, uint16_t y, uint8_t R, uint8_t G, uint8_t B) {
    this->bmp[y * width + x].R = R;
    this->bmp[y * width + x].G = G;
    this->bmp[y * width + x].B = B;
  }
  
  // 根据RGB结构设置
  void SetPixcel(uint16_t x, uint16_t y, RGB &Pix) {
    this->SetPixcel(x, y, Pix.R, Pix.G, Pix.B);
  }

};


#endif