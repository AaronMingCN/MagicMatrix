/**
 * @file MMF_DispDate_1.hpp
 * @date 2024/02/22 17:08:48
 * @author
 * @version 1.0
 * @brief 显示日期
 * @details 显示当前日期
 */

#ifndef _MMF_DISPDATE_1_HPP
#define _MMF_DISPDATE_1_HPP

#include "../MMFill.hpp"
#include "../MMHardware.hpp"
#include "MMFunc.hpp"

/// @brief 显示当前日期功能块类1
class MMF_DispDate_1 : public MMFunc {
public:
    /// @brief 构造函数
    /// @param fid 当前功能ID
    MMF_DispDate_1(uint16_t fid)
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
        int lastday = -1;
        do { // 等待并询问退出
            now = mmhardware.Rtc.GetDateTime();
            if (now.Day() != lastday) {
                lastday = now.Day();
                mmhardware.matrix.clear();
                sprintf(buff, "%2d", now.Month());
                mmhardware.matrix.setCursor(4, 0);
                mmhardware.matrix.setTextColor(mmhardware.matrix.Color(255, 0, 0));
                mmhardware.matrix.print(buff);
                mmhardware.matrix.setCursor(-2, 8);
                mmhardware.matrix.setTextColor(mmhardware.matrix.Color(255, 255, 0));
                mmhardware.matrix.print('-');

                sprintf(buff, "%2d", now.Day());
                mmhardware.matrix.setCursor(4, 8);
                mmhardware.matrix.setTextColor(mmhardware.matrix.Color(0, 255, 255));
                mmhardware.matrix.print(buff);

                mmhardware.matrix.show();
            }
        } while (IDelay->IDelay(100));
        return EXECR_OK;
    }
};

#endif