/**
 * @file MMF_Stopwatch.hpp
 * @date 2024/04/08 18:38:23
 * @author
 * @version 1.0
 * @brief 计时器
 * @details 计时器模块，用于统计消耗的时间
 */

#ifndef _MMF_STOPWATCH_HPP
#define _MMF_STOPWATCH_HPP

#include "../MMFill.hpp"
#include "MMFunc.hpp"
#include "MMScr.hpp"

/// @brief 计时器功能模块类
class MMF_StopWatch : public MMFunc {
public:
    /// @brief 构造函数
    /// @param fid 当前功能ID
    MMF_StopWatch(uint16_t fid)
        : MMFunc(fid)
    {
    }

    /// @brief 经过的时间
    unsigned long TickPass = 0;
    /// @brief 开始的时间
    unsigned long TickStart = 0;
    /// @brief 是否进行中
    bool Running = false;

    /// @brief 剩余分钟
    uint16_t CurrRMinu = 0;
    /// @brief 剩余秒钟
    uint16_t CurrRSec = 0;
    /// @brief 剩余的100毫秒数
    uint16_t CurrR100M = 0;
    /// @brief 下一个剩余分钟，避免重复绘图
    uint16_t NextRMinu = 0;
    /// @brief 下一个剩余秒钟
    uint16_t NextRSec = 0;
    /// @brief 下一个100毫秒数
    uint16_t NextR100M = 0;

    /// @brief 显示经过时间
    void Disp()
    {
        const uint8_t y1 = 2; // 第一行的y值
        const uint8_t y2 = 9; // 第二行的y值
        RGB white = { 255, 255, 255 };
        mmscr.SetEmpty();
        char buff[6] = {}; // 用于保存格式化后字符串的缓存
        sprintf(buff, "%03d", CurrRMinu);
        mmgrap.DrawMMStr(1, y1, String(buff), &mmscr, false, NULL, MMCStyle::Styles[1]);
        sprintf(buff, "%02d", CurrRSec);

        if (this->CurrRSec % 2)
            mmgrap.DrawChar(13, y1, ':', &mmscr, false, &white, NULL);

        mmgrap.DrawMMStr(1, y2, String(buff), &mmscr, false, NULL, MMCStyle::Styles[2]);
        mmgrap.DrawChar(9, y2, '.', &mmscr, false, &white, NULL);
        sprintf(buff, "%1d", CurrR100M);
        mmgrap.DrawMMStr(11, y2, String(buff), &mmscr, false, NULL, MMCStyle::Styles[3]);
        mmhardware.matrix.show();
    }

    /// @brief 如果改变了则绘制，避免重复绘图
    /// @return 是否完成了绘制
    bool DispIfChange()
    {
        bool r = false;
        // 如果时间发生改变则开始绘图
        if ((CurrRMinu != NextRMinu) || (CurrRSec != NextRSec) || (CurrR100M != NextR100M)) {
            CurrRMinu = NextRMinu; // 将新的时间更新，并重新绘制
            CurrRSec = NextRSec;
            CurrR100M = NextR100M;
            this->Disp();
            r = true;
        }
        return r;
    }

    /// @brief 准备好显示的时间数据
    void PrepareTime()
    {
        // 剩余毫秒数除以60000得到分钟数
        this->NextRMinu = this->TickPass / 60000;
        // 剩余毫秒数除以1000得到秒数，然后对60取模得到秒数
        this->NextRSec = (this->TickPass / 1000) % 60;
        // 剩余的100毫秒数,先对1000取模然后再整除100
        this->NextR100M = (this->TickPass % 1000) / 100;
    }

    /// @brief 执行功能
    /// @param IDelay 询问等待接口
    /// @return 执行结果
    virtual MMFExecR_t Exec(InquireDelay* IDelay)
    {
        this->Disp();
        uint16_t irk = 0; // 定义红外线按键值
        while (IDelay->IDelay(150, irk, true)) {
            switch (irk) {
            case IRK_UP:
                break;
            case IRK_DOWN:
                if (!this->Running) { // 如果不在运行中
                    this->TickPass = 0;
                }
                break;
            case IRK_RIGHT:
                if (!this->Running) {
                    this->Running = true;
                    if (!this->TickPass) { // 如果没有开始，则设置计数时间
                        this->TickStart = millis();
                    } else {
                        this->TickStart = millis() - this->TickPass;
                    }
                }
                break;
            case IRK_LEFT:
                this->Running = false;
                break;
            case IRK_SET: // 按set键开始
                break;
            default:
                break;
            }
            // 计算经过的时间
            if (this->Running)
                this->TickPass = mmhardware.TickPassed(this->TickStart, millis());
            this->PrepareTime();
            this->DispIfChange();
        }
        return EXECR_OK;
    }
};
#endif