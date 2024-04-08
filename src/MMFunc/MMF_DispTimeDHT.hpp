/**
 * @file MMF_DispTimeDHT.hpp
 * @date 2024/04/07 14:42:36
 * @author  
 * @version 1.0
 * @brief 显示时间温湿度
 * @details 同时显示时间和温湿度
 */

#ifndef _MMF_DISPTIMEDHT_HPP
#define _MMF_DISPTIMEDHT_HPP

#include "../MMFill.hpp"
#include "MMFunc.hpp"
#include "MMScr.hpp"

/// @brief 显示时间和温湿度功能模块
class MMF_DispTimeDHT : public MMFunc {
public:
    /// @brief 构造函数
    /// @param fid 当前功能ID
    MMF_DispTimeDHT(uint16_t fid)
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
        int lastsec = -1;
        const uint8_t y1 = 0; // 第一行的y值
        const uint8_t y2 = 6; // 第二行的y值
        const uint8_t y3 = 11; // 第三行的y值
        RGB white = { 255, 255, 255 }; // 定义红色
        RGB clT = { 255, 255, 0 }; // 
        RGB clH = { 0, 255, 255};
        // RGB red = { 255,0 , 0};

        mmhardware.dht.begin();

        do { // 等待并询问退出
            now = mmhardware.Rtc.GetDateTime();
            if (now.Second() != lastsec) {
                lastsec = now.Second();
                mmhardware.matrix.clear();

                sprintf(buff, "%02d", now.Hour());
                mmgrap.DrawMMStr(0, y1, String(buff), &mmscr, false, NULL, MMCStyle::Styles[3]);
                if (now.Second() % 2) {
                    mmgrap.DrawChar(8, y1, ':', &mmscr, false, &white);
                } else
                    mmgrap.DrawChar(8, y1, ' ', &mmscr, false, &white);

                sprintf(buff, "%02d", now.Minute());
                mmgrap.DrawMMStr(9, y1, String(buff), &mmscr, false, NULL, MMCStyle::Styles[3]);

                // 定义温湿度状态实例，并从传感器读取
                sensors_event_t event_t;
                mmhardware.dht.temperature().getEvent(&event_t);
                int T = int(event_t.temperature);

                sensors_event_t event_h;
                int H = -1; // 避免读取失败的问题
                while (H < 0 || H > 99) {
                    mmhardware.dht.humidity().getEvent(&event_h);
                    H = int(event_h.relative_humidity);
                }


                sprintf(buff, "%3d", T);
                mmgrap.DrawMMStr(0, y2, String(buff), &mmscr, false, &clT, NULL);
                mmgrap.DrawChar(13, y2, 'C', &mmscr, false, NULL, MMCStyle::Styles[0]);

                if (0 <= H && H < 100) { // 避免错误绘图
                    sprintf(buff, "%3d", H);
                    mmgrap.DrawMMStr(0, y3, String(buff), &mmscr, false, &clH);
                    mmgrap.DrawChar(13, y3, 'P', &mmscr, false, NULL, MMCStyle::Styles[2]);
                }

                mmhardware.matrix.show();
            }
        } while (IDelay->IDelay(100));
        return EXECR_OK;
    }
};

#endif