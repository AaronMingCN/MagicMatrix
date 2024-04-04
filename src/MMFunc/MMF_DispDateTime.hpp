/**
 * @file MMF_DispDateTime.hpp
 * @date 2024/04/03 00:03:32
 * @author Aaron Ming
 * @version 1.0
 * @brief 显示日期时间
 * @details 同时显示日期时间
 */

#ifndef _MMF_DISPDATETIME_HPP
#define _MMF_DISPDATETIME_HPP

#include "../MMFill.hpp"
#include "MMFunc.hpp"
#include "MMScr.hpp"

/// @brief 显示日期时间
class MMF_DispDateTime : public MMFunc {
public:
    /// @brief 构造函数
    /// @param fid 当前功能ID
    MMF_DispDateTime(uint16_t fid)
        : MMFunc(fid)
    {
    }

    /// @brief 执行功能
    /// @param IDelay 询问等待接口
    /// @return 执行结果
    virtual MMFExecR_t Exec(InquireDelay* IDelay)
    {
        char buff[8] = {};
        // UART_USB.println("Disp Time");
        RtcDateTime now; // 读取当前时间
        mmhardware.matrix.setTextSize(1);
        int lastsec = -1;
        const uint8_t y1 = 2; // 第一行的y值
        const uint8_t y2 = 9; // 第二行的y值
        RGB white = {255, 255 ,255}; // 定义红色

        do { // 等待并询问退出
            now = mmhardware.Rtc.GetDateTime();
            if (now.Second() != lastsec) {
                lastsec = now.Second();
                mmhardware.matrix.clear();

                sprintf(buff, "%2d", now.Month());
                mmgrap.DrawMMStr(0, y1, String(buff), &mmscr, false, NULL, MMCStyle::Styles[2]);
                sprintf(buff, "%-2d", now.Day());
                mmgrap.DrawMMStr(9, y1, String(buff), &mmscr, false, NULL, MMCStyle::Styles[2]);

                sprintf(buff, "%02d", now.Hour());
                mmgrap.DrawMMStr(0, y2, String(buff), &mmscr, false, NULL, MMCStyle::Styles[3]);
                if (now.Second() % 2) {
                    mmgrap.DrawChar(8, y2, ':', &mmscr, false, &white);
                } else
                    mmgrap.DrawChar(8, y2, ' ', &mmscr, false, &white);

                sprintf(buff, "%02d", now.Minute());
                mmgrap.DrawMMStr(9, y2, String(buff), &mmscr, false, NULL, MMCStyle::Styles[3]);

                mmhardware.matrix.show();
            }
        } while (IDelay->IDelay(100));
        return EXECR_OK;
    }
};

#endif
