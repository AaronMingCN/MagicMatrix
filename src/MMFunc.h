//
// 常用功能封装
// 

#include "MMDefine.h"

class MMFunc {
public:
  // 清空但是不刷新
  void MSetEmpty() {
    matrix.clear();
  }

  // 更新矩阵
  void MUpdate() {
    matrix.show();
  }

  // 清空矩阵
  void MClear() {
    MSetEmpty();
    MUpdate();  
  }

  // 设置一个像素的颜色
  void MSetPixel(uint16_t x, uint16_t y, uint8_t R, uint8_t G, uint8_t B) {
    matrix.drawPixel(x, y, matrix.Color(R, G, B));
  }

} mmfunc;