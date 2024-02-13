/*
 * @File :  RamBmp.h
 * @Time :  2024/02/13 10:30:27
 * @Vers :  1.0
 * @Desc :  内存bmp位图,将位图文件保存在ram中
 */
#ifndef _RAMBMP_H 
#define _RAMBMP_H 

#include "MMDefine.h"

// 内存bmp图片
class RamBmp{
public:
  RGB *bmp = NULL; // 定义一个RGB数组
  RamBmp(uint16_t Width = M_COL, uint16_t Height = M_ROW) {
    bmp = new RGB[Height][M_ROW];
  };
  ~RamBmp() {
    delete bmp[];
  };
};




#endif