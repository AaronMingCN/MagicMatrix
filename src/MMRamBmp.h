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
  RGB *bmp = NULL; // 定义一个RGB数组
  MMRamBmp(uint16_t Width = M_WIDTH, uint16_t Height = M_HEIGHT) {
    bmp = new RGB[Height * Width]; // 根据宽和高创建RGB数组
  };
  ~MMRamBmp() {
    delete[] bmp; // 析构是释放RBG数组
  };
};




#endif