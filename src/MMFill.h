// 填充相关
#include "MMDefine.h"
#include "MMFunc.h"

// 测试每一个像素点
void PixTest(){
  for(int i = 0; i < M_ROW; ++i) { // 将所有颜色清空
    for(int j = 0; j < M_COL; ++j) {
      mmfunc.MSetPixel(j,i, 255,255, 255);
      mmfunc.MUpdate();
      mmfunc.MSetEmpty();
    }
  }
  delay(100);
  mmfunc.MClear();
}

// 行填充
void RowFill() {
  for(int i = 0; i < M_ROW; ++i) { // 将所有颜色清空
    for(int j = 0; j < M_COL; ++j) {
      mmfunc.MSetPixel(j,i, 255, (i * 255 / M_COL), 0);
    }
    delay(100);
    mmfunc.MUpdate();
  }
  mmfunc.MClear();
}

// 列填充
void ColFill() {
  for(int j = 0; j < M_COL; ++j) {
    for(int i = 0; i < M_ROW; ++i) { 
      mmfunc.MSetPixel(j,i, 255, (i * 255 / M_COL), 0);
    }
    delay(100);
  mmfunc.MUpdate();
  }
  mmfunc.MSetEmpty();
}

// 对角线填充
void DiagFill() {
  for(int i = 0; i < M_COL; ++i) {
    int r = i, c = i;
    while(r < M_ROW && c >= 0) {
      mmfunc.MSetPixel(c,r, 255, (i * 255 / M_COL), 0); 
      ++r, --c;       
    }
    r = i, c = i;
    while(r >= 0 && c < M_COL) {
      mmfunc.MSetPixel(c,r, 255, (i * 255 / M_COL), 0);
      --r, ++c;       
    }
    delay(100);
    mmfunc.MUpdate();
  }
  mmfunc.MSetEmpty();
  
}

// 对角线填充
void DiagFill_1(){
  for(int i = 0; i < M_ROW; ++i) {
    int r = i, c = 0;
    while (r >= 0) {
      mmfunc.MSetPixel(c,r, 255, (r * 255 / M_ROW), (c * 255 / M_COL));
      --r, ++c;
    }
    delay(50);
    mmfunc.MUpdate();
  }

  for(int i = 0; i < M_COL; ++i) {
    int r = M_ROW, c = i;
    while (c < M_COL) {
      mmfunc.MSetPixel(c,r, 255, (r * 255 / M_ROW), (c * 255 / M_COL));
      --r, ++c;
    }
    delay(50);
    mmfunc.MUpdate();
  }
  mmfunc.MSetEmpty();
}

// 蛇形填充
void SnakeFill() {
  for (int i = 0; i < M_ROW; ++i) { // 行循环
    if (i % 2) 
      for(int j = M_COL - 1; j >= 0; --j) {
        mmfunc.MSetPixel(j,i, 255, (i * 255 / M_ROW), (j * 255 / M_COL));
        mmfunc.MUpdate();
        delay(10);
      }    
    else 
      for(int j = 0; j < M_COL; ++j) {
        mmfunc.MSetPixel(j,i, 255, (i * 255 / M_ROW), (j * 255 / M_COL));
        mmfunc.MUpdate();
        delay(10);
      }
  }
  mmfunc.MSetEmpty();
}

// 矩形填充
void RectFill() {
  for (int i = 0; i < M_ROW / 2; ++i) {
    for (int j = i; j < M_COL - i; ++j) 
      mmfunc.MSetPixel(j,i, 255, (i * 255 / M_ROW), (j * 255 / M_COL));
    for (int j = i; j < M_ROW - i; ++j) 
      mmfunc.MSetPixel(i,j, 255, (i * 255 / M_ROW), (j * 255 / M_COL));
    for (int j = (M_COL - i - 1); j >= i; --j) 
      mmfunc.MSetPixel(j,M_ROW - i - 1, 255, (i * 255 / M_ROW), (j * 255 / M_COL));
    for (int j = (M_ROW - i - 1); j >= i; --j) 
      mmfunc.MSetPixel(M_ROW - i - 1,j, 255, (i * 255 / M_ROW), (j * 255 / M_COL));
    mmfunc.MUpdate();
    delay(200);
  }
  matrix.clear();
  
}

// 填充整个屏幕
void Fill(uint8_t R, uint8_t G, uint8_t B) {
  for(uint8_t r = 0; r < M_ROW; ++r) { // 将所有颜色清空
    for(uint8_t c = 0; c < M_COL; ++c) {
      matrix.drawPixel(c,r, matrix.Color(R, G, B));
    }
  }
}

// 测试矩阵
void MatrixTest() {
  Fill(255, 0, 0);
  mmfunc.MUpdate();
  delay(500);
  Fill(0, 255, 0);
  mmfunc.MUpdate();
  delay(500);
  Fill(0, 0, 255);
  mmfunc.MUpdate();
  delay(500);
  matrix.clear();
  mmfunc.MUpdate();  
}

// 警灯闪烁
void AlarmLamp() {
  for(uint8_t i = 0; i < 10; ++i) {

    Fill(255, 0, 0);
    mmfunc.MUpdate();
    delay(100);
    Fill(0, 0, 255);
    mmfunc.MUpdate();
    delay(100);    
  }
}
// // 蛇形回旋填充
// void RectSnakeFill() { 
//   // 宏定义四个方向 顺时针+1 逆时针-1
//   #define D_U (0)  // 上
//   #define D_R (1)  // 右
//   #define D_D (2)  // 下
//   #define D_L (3)  // 左
//   int dir = D_R; // 定义当前方向,默认向右
//   int r = 0, c = 0; // 定义当前的行列下标
//   int ct = 0; // 填充过的数量
//   while(ct < 63) {
//     matrix.drawPixel(c,r, matrix.Color(255,(c * 255 / M_COL), (r * 255 / M_ROW)));
//     mmfunc.MUpdate(); 
//     delay(10);
//     switch (dir) { // 根据当前方向确定下一步
//       case D_R: if (c < (M_COL - 1) && matrix.getPixel(c + 1,r) == 0) ++c, ++ct; // 如果向右可以移动
//                 else ++dir, dir %= 4;
//                 break;
//       case D_D: if (r < (M_ROW - 1) && scr[r + 1][c].R == 0) ++r, ++ct; // 如果向右可以移动
//                 else ++dir, dir %= 4;
//                 break;
//       case D_L: if (c > 0 && scr[r][c - 1].R == 0) --c, ++ct; // 如果向右可以移动
//                 else ++dir, dir %= 4;
//                 break;                
//       case D_U: if (r > 0 && scr[r - 1][c].R == 0) --r, ++ct; // 如果向右可以移动
//                 else ++dir, dir %= 4;
//                 break;                
//     }
//   }
//   matrix.drawPixel(c,r, matrix.Color(255,(c * 255 / M_COL), (r * 255 / M_ROW));
//   mmfunc.MUpdate();   
//   delay(10);
// }


