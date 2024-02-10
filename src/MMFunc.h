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
} mmfunc;