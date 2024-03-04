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
    // 构造
    MMF_DispTime_1(uint16_t fid)
        : MMFunc(fid)
    {
    }

    // 执行功能
    virtual MMFExecR_t Exec(InquireDelay *IDelay)
    {
        char buff[8] = {};
        // UART_USB.println("Disp Time");
        RtcDateTime now; // 读取当前时间
        mmhardware.matrix.setTextSize(1);
        int lastsec = -1;
        do { // 等待并询问退出
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
        } while(IDelay->IDelay(100));
        return EXECR_OK;
    }
};

#endif