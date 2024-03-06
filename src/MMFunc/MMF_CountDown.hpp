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
    uint16_t CurrRMinu = 0; // 剩余分钟
    uint16_t CurrRSec = 0; // 剩余秒钟
    uint16_t NextRMinu = 0; // 下一个剩余分钟，避免重复绘图
    uint16_t NextRSec = 0; // 下一个剩余秒钟
    // 显示剩余时间
    void DispRemain()
    {
        char buff[5] = {}; // 用于保存格式化后字符串的缓存
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

    virtual MMFExecR_t Exec(InquireDelay* IDelay)
    {
        bool bp = true;
        this->DispRemain();
        uint16_t irk = 0; // 定义红外线按键值
        do {
            if (mmhardware.IRRCode(irk, true)) { // 读取红外线值
                switch (irk) {
                case IRK_UP:
                    NextRMinu += 5;
                    break;
                case IRK_DOWN:
                    NextRMinu -= 5;
                    break;
                case IRK_LEFT:
                    ++NextRMinu;
                    break;
                case IRK_RIGHT:
                    --NextRMinu;
                    break;
                case IRK_SET: // 按set键开始
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
};

#endif