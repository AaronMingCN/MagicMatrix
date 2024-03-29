/**
 * @file MMGrap.hpp
 * @date 2024/02/13 10:36:51
 * @author Aaron Ming 
 * @version 1.0
 * @brief 图像相关的定义
 * @details 
 */

#ifndef _MMGRAP_HPP
#define _MMGRAP_HPP

#include "MMDefine.hpp"
#include "MMScr.hpp"
#include "MMRamBmp.hpp"
#include "MMSD.hpp"
#include "MMHardware.hpp"
#include "MMCharDefine.hpp"
#include "MMCanvas.hpp"



/// @brief 图像相关共功能类
class MMGrap {
public:
    /// @brief 显示LOGO
    void DispLOGO() {
        MMRamBmp rb;
        mmsd.LoadBitmapToRamBmp(FILENAME_LOGO, rb);
        
        for (uint8_t i = 0; i < M_BRIGHT; i += 1)
        {
            mmhardware.matrix.setBrightness(i);
            mmscr.DrawRamBmp(rb);
            mmscr.Update();
            delay(10);
        }
        delay(1500);
        for (uint8_t i = 0; i < M_BRIGHT; i += 1)
        {
            mmhardware.matrix.setBrightness(M_BRIGHT - i);
            mmscr.DrawRamBmp(rb);
            mmscr.Update();
            delay(10);
        }
        mmhardware.matrix.setBrightness(M_BRIGHT);        

    }


/// @brief 在MMCanvas指定位置绘制MM字符
/// @param x 横向值
/// @param y 纵向值
/// @param mmc 绘制的MM字符
/// @param color 用于绘制的颜色的地址,为空时默认使用红色
/// @param Canvas 目标画布 
/// @param ondraw 在绘制时的回调
void DrawChar(int16_t x, int16_t y, uint16_t mmc, MMCanvas *Canvas, RGB *color = NULL,OnDrawChar ondraw = NULL) {
    RGB rgb = {};
    if (color) rgb = *color;
    else rgb = {255, 0, 0};

	for (int16_t i = 0; i < MMCHAR_HEIGHT; ++i) {
		for (int16_t j = 0; j < MMCHAR_WIDTH; ++j) {
			mmc <<= 1;
			if (mmc & 0b1000000000000000) {
				// a[i + y][j + x] = true;
                if (ondraw) (*ondraw)(j, i, j + x, i + y, rgb); // 如果定义了绘图时的回调则先调用
                Canvas->SetPixel(j + x, i + y, rgb);
			}
		}
	}
}    
} mmgrap;

#endif
