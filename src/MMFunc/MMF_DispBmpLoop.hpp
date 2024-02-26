/*
 * @File :  MMF_DispBmpLoop.hpp
 * @Time :  2024/02/26 13:39:43
 * @Auth :
 * @Vers :  1.0
 * @Desc :  循环播放bmp图片
 */

#ifndef _MMF_DISPBMPLOOP_HPP
#define _MMF_DISPBMPLOOP_HPP

#include "../MMFill.hpp"
#include "MMFunc.hpp"
#include "MMSD.hpp"
#include "MMScr.hpp"

// 矩阵屏幕测试类，测试RGB显示
class MMF_DispBmpLoop : public MMFunc {
public:
    MMF_DispBmpLoop(uint16_t fid)
        : MMFunc(fid)
    {
    }
    virtual MMFExecR_t Exec(InquireDelay* IDelay)
    {
        do {
            digitalWrite(PIN_LED_BUILTIN, HIGH);
            mmsd.DrawBitmap("pixil1.bmp");
            digitalWrite(PIN_LED_BUILTIN, LOW);
            mmscr.Update();
            if (!(IDelay->IDelay(500))) break;

            digitalWrite(PIN_LED_BUILTIN, HIGH);
            mmsd.DrawBitmap("pixil2.bmp");
            digitalWrite(PIN_LED_BUILTIN, LOW);
            mmscr.Update();
            if (!(IDelay->IDelay(500))) break;

            digitalWrite(PIN_LED_BUILTIN, HIGH);
            mmsd.DrawBitmap("pixil3.bmp");
            digitalWrite(PIN_LED_BUILTIN, LOW);
            mmscr.Update();
            if (!(IDelay->IDelay(500))) break;

            digitalWrite(PIN_LED_BUILTIN, HIGH);
            mmsd.DrawBitmap("pixil4.bmp");
            digitalWrite(PIN_LED_BUILTIN, LOW);
            mmscr.Update();
            if (!(IDelay->IDelay(500))) break;
        } while (IDelay->Inquire());
        return EXECR_OK;
    }
};

#endif