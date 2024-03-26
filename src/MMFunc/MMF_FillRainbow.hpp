/**
 * @file MMF_FillRainbow.hpp
 * @date 2024/02/26 16:59:45
 * @author Aaron Ming
 * @version 1.0
 * @brief 彩虹填充
 * @details
 */

#ifndef _MMF_FILLRAINBOW_HPP
#define _MMF_FILLRAINBOW_HPP

#include "../MMFill.hpp"
#include "MMFunc.hpp"
#include "MMScr.hpp"

// 矩阵屏幕测试类，测试RGB显示

/// @brief 彩虹填充
class MMF_FillRainbow : public MMFunc {
public:
    /// @brief 构造函数
    /// @param fid 当前功能ID
    MMF_FillRainbow(uint16_t fid)
        : MMFunc(fid)
    {
    }

    /// @brief 执行功能
    /// @param IDelay 询问等待接口
    /// @return 执行结果
    virtual MMFExecR_t Exec(InquireDelay* IDelay)
    {
        do {

            for (int i = 0; i < M_HEIGHT; ++i) {
                int r = i, c = 0;
                while (r >= 0) {
                    mmscr.SetPixel(c, r, 255, (r * 255 / M_HEIGHT), (c * 255 / M_WIDTH));
                    --r, ++c;
                }
                if (!IDelay->IDelay(100))
                    break;
                mmscr.Update();
                while (mmhardware.matrix.availableForWrite())
                    delay(10); // 等待设备就绪
            }

            for (int i = 0; i < M_WIDTH; ++i) {
                int r = M_HEIGHT, c = i;
                while (c < M_WIDTH) {
                    mmscr.SetPixel(c, r, 255, (r * 255 / M_HEIGHT), (c * 255 / M_WIDTH));
                    --r, ++c;
                }
                if (!IDelay->IDelay(100))
                    break;
                mmscr.Update();
                while (mmhardware.matrix.availableForWrite())
                    delay(10); // 等待设备就绪
            }
            mmscr.SetEmpty();

        } while (IDelay->IDelay(100));
        return EXECR_OK;
    }
};

#endif