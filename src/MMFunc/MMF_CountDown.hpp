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
#include "MMScr.hpp"

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
    /// @brief 下一个剩余分钟，避免重复绘图
    uint16_t NextRMinu = 0;
    /// @brief 下一个剩余秒钟
    uint16_t NextRSec = 0;

    /// @brief 显示剩余时间
    void DispRemain()
    {
        char buff[6] = {}; // 用于保存格式化后字符串的缓存
        mmhardware.matrix.clear();
        mmhardware.matrix.setCursor(2, 0);
        mmhardware.matrix.setTextColor(RGB::Color(255, 255, 0));
        sprintf(buff, "%02d", CurrRMinu);
        mmhardware.matrix.print(buff);
        mmhardware.matrix.setCursor(2, 9);
        mmhardware.matrix.setTextColor(RGB::Color(0, 255, 255));
        sprintf(buff, "%02d", CurrRSec);
        mmhardware.matrix.print(buff);
        mmhardware.matrix.show();
    }

    /// @brief 准备好显示的时间数据
    void PrepareTime()
    {
        // 剩余毫秒数除以60000得到分钟数
        this->NextRMinu = this->RemainMill / 60000;
        // 剩余毫秒数除以1000得到秒数，然后对60取模得到秒数
        this->NextRSec = (this->RemainMill / 1000) % 60;
    }

    /// @brief 执行倒计时
    /// @param IDelay : 传入询问等待接口用于相应功能切换
    void CountDown(InquireDelay* IDelay)
    {
        while (IDelay->IDelay(100)) {
            unsigned long now = millis(); // 取当前开机时间
            unsigned long pass = mmhardware.TickPassed(this->LastCount, now); // 计算距离上次计数的时间
            this->LastCount = now;
            if (this->RemainMill >= pass)
                this->RemainMill -= pass;
            else {
                this->RemainMill = 0;
                this->Alert(IDelay);
            }
            this->PrepareTime();
            // if (this->CurrRMinu == 0 && this->CurrRSec == 0)
            //     this->Alert(IDelay);
            this->DispRemainChange();
        }
    }

    /// @brief 如果改变了则绘制，避免重复绘图
    /// @return 是否完成了绘制
    bool DispRemainChange()
    {
        bool r = false;
        // 如果分数发生改变则开始绘图
        if ((CurrRMinu != NextRMinu) || (CurrRSec != NextRSec)) {
            CurrRMinu = NextRMinu;
            CurrRSec = NextRSec;
            this->DispRemain();
            r = true;
        }
        return r;
    }

    /// @brief 计算剩余时间
    void CalRemainMill()
    {
        this->RemainMill = NextRMinu * 60000 + NextRSec * 1000;
        this->LastCount = millis();
    }

    /// @brief 执行功能块
    /// @param IDelay : 询问等待接口
    /// @return 执行结果
    virtual MMFExecR_t Exec(InquireDelay* IDelay)
    {
        this->DispRemain();
        uint16_t irk = 0; // 定义红外线按键值
        while (IDelay->Inquire(irk)) {
            switch (irk) {
            case IRK_UP:
                if (NextRMinu <= 94) {
                    NextRMinu += 5;
                }
                break;
            case IRK_DOWN:
                if (NextRMinu >= 5) {
                    NextRMinu -= 5;
                } else
                    NextRSec = 0; // 如果分钟已经无法再减少了则将秒置零
                break;
            case IRK_RIGHT:
                if (NextRMinu <= 98) {
                    ++NextRMinu;
                }
                break;
            case IRK_LEFT:
                if (NextRMinu >= 1) {
                    --NextRMinu;
                } else
                    NextRSec = 0; // 如果分钟已经无法再减少了则将秒置零
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