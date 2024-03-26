/**
 * @file MMF_DispDHT_1.hpp
 * @date 2024/02/22 17:56:41
 * @author
 * @version 1.0
 * @brief 显示环境温湿度
 * @details 
 */

#ifndef _MMF_DISPDHT_1_HPP
#define _MMF_DISPDHT_1_HPP

#include "../MMFill.hpp"
#include "../MMHardware.hpp"
#include "MMFunc.hpp"

/// @brief 显示环境温湿度功能块类1
class MMF_DispDHT_1 : public MMFunc {
public:
    /// @brief 构造函数
    /// @param fid 当前功能ID
    MMF_DispDHT_1(uint16_t fid)
        : MMFunc(fid)
    {
    }

    /// @brief 执行功能
    /// @param IDelay 询问等待接口
    /// @return 执行结果
    virtual MMFExecR_t Exec(InquireDelay* IDelay)
    {
        char buff[8] = {};

        // 定义上一次的温度和湿度，避免冗余绘图
        int lastT = 100;
        int lastH = 100;
        mmhardware.dht.begin();
        do {
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

                if (0 <= H && H < 100) { // 避免错误绘图
                    sprintf(buff, "%-2d", H);
                    mmhardware.matrix.setCursor(0, 8);
                    mmhardware.matrix.setTextColor(RGB::Color(0, 255, 0));
                    mmhardware.matrix.print(buff);

                    mmhardware.matrix.setCursor(11, 8);
                    mmhardware.matrix.setTextColor(RGB::Color(0, 0, 255));
                    mmhardware.matrix.print('%');
                }

                mmhardware.matrix.show();
            }
        } while (IDelay->IDelay(1000)); // 等待并询问退出
        return EXECR_OK;
    }
};

#endif