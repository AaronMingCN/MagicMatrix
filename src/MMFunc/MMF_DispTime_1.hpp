/*
 * @File :  MMF_DispTime_1.hpp
 * @Time :  2024/02/16 20:18:00
 * @Auth :
 * @Vers :  1.0
 * @Desc :  时间显示模块1
 */

#ifndef _MMF_DISPTIME_1_HPP
#define _MMF_DISPTIME_1_HPP

#include "../MMFill.hpp"
#include "../MMHardware.hpp"
#include "MMFunc.hpp"

// 时间显示界面1
class MMF_DispTime_1 : public MMFunc {
public:
    MMF_DispTime_1(uint16_t fid)
        : MMFunc(fid)
    {
    }
    char buff[8] = {};
    virtual uint16_t Exec()
    {
        RtcDateTime now;
        mmhardware.matrix.setTextSize(1);
        int lastsec = -1;
        for (int i = 0; i < 1000; ++i) {
            now = mmhardware.Rtc.GetDateTime();
            if (now.Second() != lastsec) {
                lastsec = now.Second();
                mmhardware.matrix.clear();
                sprintf(buff, "%02d", now.Hour());
                mmhardware.matrix.setCursor(4, 0);
                mmhardware.matrix.setTextColor(RGB::Color(255, 0, 255));
                mmhardware.matrix.print(buff);

                if (now.Second() % 2) {
                    mmhardware.matrix.setCursor(0, 8);
                    mmhardware.matrix.setTextColor(RGB::Color(0, 255, 255));
                    mmhardware.matrix.print(':');
                } else
                    mmhardware.matrix.print(' ');

                sprintf(buff, "%02d", now.Minute());
                mmhardware.matrix.setCursor(4, 8);
                mmhardware.matrix.setTextColor(RGB::Color(255, 255, 0));
                mmhardware.matrix.print(buff);

                // mmhardware.matrix.setCursor(10, 1);
                mmhardware.matrix.print(':');
                mmhardware.matrix.show();
            }
            delay(10);
        }

        return EXECR_OK;
    }
};

#endif