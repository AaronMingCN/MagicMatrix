/*
 * @File :  MMScr.h
 * @Time :  2024/02/13 10:33:34
 * @Vers :  1.0
 * @Desc :  矩阵显示功能封装
 */
#ifndef _MMSCR_H
#define _MMSCR_H

#include "MMDefine.h"


class MMScr {
public:
  // 清空但是不刷新
  void SetEmpty() {
    matrix.clear();
  }

  // 更新矩阵
  void Update() {
    matrix.show();
  }

  // 清空矩阵，并立刻显示
  void Clear() {
    SetEmpty();
    Update();  
  }

  // 设置一个像素的颜色
  void SetPixel(uint16_t x, uint16_t y, uint8_t R, uint8_t G, uint8_t B) {
    matrix.drawPixel(x, y, matrix.Color(R, G, B));
  }

  // 填充整个屏幕
  void Fill(uint8_t R, uint8_t G, uint8_t B) {
    for(uint8_t r = 0; r < M_HEIGHT; ++r) { // 将所有颜色清空
      for(uint8_t c = 0; c < M_WIDTH; ++c) {
        matrix.drawPixel(c,r, matrix.Color(R, G, B));
      }
    }
  }

} mmscr;

#endif