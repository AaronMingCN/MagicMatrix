/*
 * @File :  MMGrap.hpp
 * @Time :  2024/02/13 10:36:51
 * @Auth :  
 * @Vers :  1.0
 * @Desc :  图像相关的定义
 */
#ifndef _MMGRAP_HPP
#define _MMGRAP_HPP

#include "MMDefine.hpp"
#include "MMLOGO.hpp"
#include "MMScr.hpp"
#include "MMRamBmp.hpp"
#include "MMSD.hpp"
#include "MMHardware.hpp"

// MagicMatrix图像相关定义
class MMGrap {
public:
    // 显示LOGO
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
} mmgrap;

#endif
