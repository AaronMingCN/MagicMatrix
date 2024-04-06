/**
 * @file MMF_CountDown.hpp
 * @date 2024/03/06 19:44:55
 * @author Aaron Ming
 * @version 1.0
 * @brief 倒计时功能模块
 * @details 设定倒计时时间，开始倒计时，计时为0时响铃提醒
 ***/

#ifndef _MMF_COUTNDOWN_HPP
#define _MMF_COUTNDOWN_HPP

#include "../MMFill.hpp"
#include "MMFunc.hpp"
// #include "MMScr.hpp"

/// @brief 倒计时模块
class MMF_CountDown : public MMFunc {
public:
    /// @brief 构造函数
    /// @param fid : 功能块ID
    MMF_CountDown(uint16_t fid)
        : MMFunc(fid)
    {
    }
    /// @brief 剩余的毫秒数
    unsigned long RemainMill = 0;
    /// @brief 开始计时的开机毫秒数
    unsigned long StartMill = 0;
    /// @brief 暂停时的开机毫秒数
    unsigned long PauseMill = 0;
    /// @brief 最后计数的时间
    unsigned long LastCount = 0;

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

    /// @brief 显示剩余时间
    void DispRemain()
    {
        const uint8_t y1 = 2; // 第一行的y值
        const uint8_t y2 = 9; // 第二行的y值
        RGB white = { 255, 255, 255 };
        mmscr.SetEmpty();
        char buff[6] = {}; // 用于保存格式化后字符串的缓存
        sprintf(buff, "%03d", CurrRMinu);
        mmgrap.DrawMMStr(1, y1, String(buff), &mmscr, false, NULL, MMCStyle::Styles[0]);
        sprintf(buff, "%02d", CurrRSec);

        if (this->CurrRSec % 2)
            mmgrap.DrawChar(13, y1, ':', &mmscr, false, &white, NULL);

        mmgrap.DrawMMStr(1, y2, String(buff), &mmscr, false, NULL, MMCStyle::Styles[4]);
        mmgrap.DrawChar(9, y2, '.', &mmscr, false, &white, NULL);
        sprintf(buff, "%1d", CurrR100M);
        mmgrap.DrawMMStr(11, y2, String(buff), &mmscr, false, NULL, MMCStyle::Styles[3]);
        mmhardware.matrix.show();
    }

    /// @brief 准备好显示的时间数据
    void PrepareTime()
    {
        // 剩余毫秒数除以60000得到分钟数
        this->NextRMinu = this->RemainMill / 60000;
        // 剩余毫秒数除以1000得到秒数，然后对60取模得到秒数
        this->NextRSec = (this->RemainMill / 1000) % 60;
        // 剩余的100毫秒数,先对1000取模然后再整除100
        this->NextR100M = (this->RemainMill % 1000) / 100;
    }

    /// @brief 执行倒计时
    /// @param IDelay : 传入询问等待接口用于相应功能切换
    void CountDown(InquireDelay* IDelay)
    {
        while (IDelay->IDelay(80)) {
            unsigned long now = millis(); // 取当前开机时间
            unsigned long pass = mmhardware.TickPassed(this->LastCount, now); // 计算距离上次计数的时间
            this->LastCount = now;
            if (this->RemainMill >= pass)
                this->RemainMill -= pass;
            else {
                this->RemainMill = 0;
                this->Alert(IDelay);
            }
            this->PrepareTime(); // 准备需要显示的时间
            this->DispRemainChange(); // 显示时间更改
        }
    }

    /// @brief 如果改变了则绘制，避免重复绘图
    /// @return 是否完成了绘制
    bool DispRemainChange()
    {
        bool r = false;
        // 如果时间发生改变则开始绘图
        if ((CurrRMinu != NextRMinu) || (CurrRSec != NextRSec) || (CurrR100M != NextR100M)) {
            CurrRMinu = NextRMinu; // 将新的时间更新，并重新绘制
            CurrRSec = NextRSec;
            CurrR100M = NextR100M;
            this->DispRemain();
            r = true;
        }
        return r;
    }

    /// @brief 计算剩余时间
    void CalRemainMill()
    {
        this->RemainMill = NextRMinu * 60000 + NextRSec * 1000; // 计算剩余的毫秒数
        this->LastCount = millis(); // 记录开始计时的系统毫秒数
    }

    /// @brief 执行功能块
    /// @param IDelay : 询问等待接口
    /// @return 执行结果
    virtual MMFExecR_t Exec(InquireDelay* IDelay)
    {
        this->DispRemain();
        const uint32_t MAX_MINU = 999;
        uint16_t irk = 0; // 定义红外线按键值
        while (IDelay->Inquire(irk)) {
            switch (irk) {
            case IRK_UP:
                if (NextRMinu < MAX_MINU - 5) {
                    NextRMinu += 5;
                } else
                    NextRMinu = MAX_MINU;
                break;
            case IRK_DOWN:
                if (NextRMinu >= 5) {
                    NextRMinu -= 5;
                } else {
                    NextRSec = 0; // 如果分钟已经无法再减少了则将秒置零
                    NextR100M = 0;
                }
                break;
            case IRK_RIGHT:
                if (NextRMinu < MAX_MINU) {
                    ++NextRMinu;
                }
                break;
            case IRK_LEFT:
                if (NextRMinu >= 1) {
                    --NextRMinu;
                } else {
                    NextRSec = 0; // 如果分钟已经无法再减少了则将秒置零
                    NextR100M = 0;
                }
                break;
            case IRK_SET: // 按set键开始
                this->CalRemainMill();
                if (this->RemainMill > 0) { // 如果计数的时间大于0则开始倒数
                    this->CountDown(IDelay);
                }
                break;
            default:
                break;
            }
            // 如果剩余时间改变则显示并等待
            if (this->DispRemainChange()) {
                IDelay->IDelay(200, irk);
            }
        }
        mmhardware.Beep(false);
        return EXECR_OK;
    }

    /// @brief 响铃
    /// @param IDelay : 询问等待接口
    void Alert(InquireDelay* IDelay)
    {
        do {
            for (size_t i = 0; i < 5; i++) {
                mmhardware.Beep(true);
                if (!IDelay->IDelay(30))
                    break;
                mmhardware.Beep(false);
                // if (!IDelay->IDelay((i + 1) * 20))
                //     break;
                if (!IDelay->IDelay(20))
                    break;
            }
            if (!IDelay->IDelay(1000))
                break;
        } while (IDelay->Inquire());
        mmhardware.Beep(false);
    }
};

#endif