/*
 * @File :  MMF_CountDown.hpp
 * @Time :  2024/03/06 19:44:55
 * @Auth :
 * @Vers :  1.0
 * @Desc :  倒计时功能模块
 */

#ifndef _MMF_COUTNDOWN_HPP
#define _MMF_COUTNDOWN_HPP

#include "../MMFill.hpp"
#include "MMFunc.hpp"
#include "MMScr.hpp"

// 倒计时模块
class MMF_CountDown : public MMFunc {
public:
    MMF_CountDown(uint16_t fid)
        : MMFunc(fid)
    {
    }
    unsigned long RemainMill = 0; // 剩余的毫秒数
    unsigned long StartMill = 0; // 开始计时的开机毫秒数
    unsigned long PauseMill = 0; // 暂停时的开机毫秒数
    unsigned long LastCount = 0; // 最后计数的时间

    uint16_t CurrRMinu = 0; // 剩余分钟
    uint16_t CurrRSec = 0; // 剩余秒钟
    uint16_t NextRMinu = 0; // 下一个剩余分钟，避免重复绘图
    uint16_t NextRSec = 0; // 下一个剩余秒钟

    // 显示剩余时间
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

    // 准备好显示的时间数据
    void PrepareTime()
    {
        this->NextRMinu = this->RemainMill / 60000;
        this->NextRSec = (this->RemainMill / 1000) % 60;
    }
    // 倒计时
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

    // 如果改变了则绘制
    void DispRemainChange()
    {
        // 如果分数发生改变则开始绘图
        if ((CurrRMinu != NextRMinu) || (CurrRSec != NextRSec)) {
            CurrRMinu = NextRMinu;
            CurrRSec = NextRSec;
            this->DispRemain();
        }
    }

    // 准备剩余时间
    void CalRemainMill()
    {
        this->RemainMill = NextRMinu * 60000 + NextRSec * 1000;
        this->LastCount = millis();
    }

    virtual MMFExecR_t Exec(InquireDelay* IDelay)
    {
        this->DispRemain();
        uint16_t irk = 0; // 定义红外线按键值
        do {
            if (mmhardware.IRRCode(irk, true)) { // 读取红外线值
                switch (irk) {
                case IRK_UP:
                    if (NextRMinu <= 94)
                        NextRMinu += 5;
                    break;
                case IRK_DOWN:
                    if (NextRMinu >= 5)
                        NextRMinu -= 5;
                    else
                        NextRSec = 0; // 如果分钟已经无法再减少了则将秒置零
                    break;
                case IRK_RIGHT:
                    if (NextRMinu <= 98)
                        ++NextRMinu;
                    break;
                case IRK_LEFT:
                    if (NextRMinu >= 1)
                        --NextRMinu;
                    else
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

                this->DispRemainChange(); // 如果剩余时间改变则显示
            }
        } while (IDelay->IDelay(100));
        mmhardware.Beep(false);
        return EXECR_OK;
    }

    // 响铃
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