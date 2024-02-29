/*
 * @File :  MMF_FillRainbow.hpp
 * @Time :  2024/02/26 16:59:45
 * @Auth :
 * @Vers :  1.0
 * @Desc :  彩虹填充
 */

#ifndef _MMF_FILLRAINBOW_HPP
#define _MMF_FILLRAINBOW_HPP

#include "../MMFill.hpp"
#include "MMFunc.hpp"
#include "MMScr.hpp"

// 矩阵屏幕测试类，测试RGB显示
class MMF_FillRainbow : public MMFunc {
public:
    MMF_FillRainbow(uint16_t fid)
        : MMFunc(fid)
    {
    }
    virtual MMFExecR_t Exec(InquireDelay* IDelay)
    {
        do {

            for (int i = 0; i < M_HEIGHT; ++i) {
                int r = i, c = 0;
                while (r >= 0) {
                    mmscr.SetPixel(c, r, 255, (r * 255 / M_HEIGHT), (c * 255 / M_WIDTH));
                    --r, ++c;
                }
                if (!IDelay->IDelay(100)) break;
                mmscr.Update();
            }

            for (int i = 0; i < M_WIDTH; ++i) {
                int r = M_HEIGHT, c = i;
                while (c < M_WIDTH) {
                    mmscr.SetPixel(c, r, 255, (r * 255 / M_HEIGHT), (c * 255 / M_WIDTH));
                    --r, ++c;
                }
                if (!IDelay->IDelay(100)) break;
                mmscr.Update();
            }
            mmscr.SetEmpty();

        } while (IDelay->IDelay(100));
        return EXECR_OK;
    }
};

#endif