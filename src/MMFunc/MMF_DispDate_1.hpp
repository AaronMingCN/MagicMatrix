/*
 * @File :  MMF_DispDate_1.hpp
 * @Time :  2024/02/22 17:08:48
 * @Auth :  
 * @Vers :  1.0
 * @Desc :  显示日期
 */


#ifndef _MMF_DISPDATE_1_HPP
#define _MMF_DISPDATE_1_HPP

#include "../MMFill.hpp"
#include "../MMHardware.hpp"
#include "MMFunc.hpp"

// 时间显示界面1
class MMF_DispDate_1 : public MMFunc {
public:
    // 构造
    MMF_DispDate_1(uint16_t fid)
        : MMFunc(fid)
    {
    }

    // 执行功能
    virtual MMFExecR_t Exec(InquireDelay *IDelay)
    {
        char buff[8] = {};
        Serial.println("Disp Time");
        RtcDateTime now; // 读取当前时间
        mmhardware.matrix.setTextSize(1);
        int lastday = -1;
        do { // 等待并询问退出
            now = mmhardware.Rtc.GetDateTime();
            if (now.Day() != lastday) {
                lastday = now.Day();
                mmhardware.matrix.clear();
                sprintf(buff, "%2d", now.Month());
                mmhardware.matrix.setCursor(4, 0);
                mmhardware.matrix.setTextColor(RGB::Color(255, 0, 0));
                mmhardware.matrix.print(buff);
                mmhardware.matrix.setCursor(-2, 8);
                mmhardware.matrix.setTextColor(RGB::Color(255, 255, 0));
                mmhardware.matrix.print('-');

                sprintf(buff, "%2d", now.Day());
                mmhardware.matrix.setCursor(4, 8);
                mmhardware.matrix.setTextColor(RGB::Color(0, 255, 255));
                mmhardware.matrix.print(buff);

                mmhardware.matrix.show();
            }
        } while(IDelay->IDelay(100));
        return EXECR_OK;
    }
};

#endif