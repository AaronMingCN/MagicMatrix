/*
 * @File :  MMF_DispDHT_1.hpp
 * @Time :  2024/02/22 17:56:41
 * @Auth :
 * @Vers :  1.0
 * @Desc :  显示环境温湿度
 */

#ifndef _MMF_DISPDHT_1_HPP
#define _MMF_DISPDHT_1_HPP

#include "../MMFill.hpp"
#include "../MMHardware.hpp"
#include "MMFunc.hpp"

// 时间显示界面1
class MMF_DispDHT_1 : public MMFunc {
public:
    // 构造
    MMF_DispDHT_1(uint16_t fid)
        : MMFunc(fid)
    {
    }

    // 执行功能
    virtual MMFExecR_t Exec(InquireDelay* IDelay)
    {
        char buff[8] = {};

        // 定义上一次的温度和湿度，避免冗余绘图
        int lastT = 100;
        int lastH = 100;
        do { 
            // 跟别定义温湿度状态实例，并从传感器读取
            sensors_event_t event_t;
            mmhardware.dht.temperature().getEvent(&event_t);
            int T = int(event_t.temperature);
            sensors_event_t event_h;
            mmhardware.dht.humidity().getEvent(&event_h);
            int H = int(event_h.relative_humidity);

            if (lastT != T || lastH != H) { // 解决冗余绘图问题
                lastT = T;
                lastH = H;
                // lastsec = now.Second();
                mmhardware.matrix.clear();
                sprintf(buff, "%3d", T);
                // sprintf(buff, "%3d", int(-11));
                mmhardware.matrix.setCursor(-1, 0);
                mmhardware.matrix.setTextColor(RGB::Color(255, 255, 0));
                mmhardware.matrix.print(buff);

                sprintf(buff, "%-2d", H);
                mmhardware.matrix.setCursor(0, 8);
                mmhardware.matrix.setTextColor(RGB::Color(0, 255, 0));
                mmhardware.matrix.print(buff);

                mmhardware.matrix.setCursor(11, 8);
                mmhardware.matrix.setTextColor(RGB::Color(0, 0, 255));
                mmhardware.matrix.print('%');

                mmhardware.matrix.show();
            }
        } while (IDelay->IDelay(1000)); // 等待并询问退出
        return EXECR_OK;
    }
};

#endif