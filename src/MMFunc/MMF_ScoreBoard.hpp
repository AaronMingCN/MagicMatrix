/*
 * @File :  MMF_ScoreBoard.hpp
 * @Time :  2024/02/29 22:45:38
 * @Auth :
 * @Vers :  1.0
 * @Desc :  记分牌
 */

#ifndef _MMF_SCOREBOARD_HPP
#define _MMF_SCOREBOARD_HPP

#include "../MMFill.hpp"
#include "MMFunc.hpp"
#include "MMScr.hpp"

// 记分牌功能
class MMF_ScoreBoard : public MMFunc {
public:
    int CurrScoreA = 0; // 第一个分数
    int CurrScoreB = 0; // 第二个分数
    int NextScoreA = 0; // 避免重复绘图
    int NextScoreB = 0;
    MMF_ScoreBoard(uint16_t fid)
        : MMFunc(fid)
    {
    }

    // 显示分数
    void DispScore()
    {
        char buff[5] = {}; // 用于保存格式化后字符串的缓存
        mmhardware.matrix.clear();
        mmhardware.matrix.setCursor(-1, 0);
        mmhardware.matrix.setTextColor(RGB::Color(255, 0, 0));
        sprintf(buff, "%3d", CurrScoreA);
        mmhardware.matrix.print(buff);
        mmhardware.matrix.setCursor(-1, 9);
        mmhardware.matrix.setTextColor(RGB::Color(0, 255, 0));
        sprintf(buff, "%3d", CurrScoreB);
        mmhardware.matrix.print(buff);
        mmhardware.matrix.show();
    }

    // 如果改变了则绘制
    void DispScoreChange()
    {
        // 如果分数发生改变则开始绘图
        if ((CurrScoreA != NextScoreA) || (CurrScoreB != NextScoreB)) {
            CurrScoreA = NextScoreA;
            CurrScoreB = NextScoreB;
            this->DispScore();
        }
    }

    // 执行功能
    virtual MMFExecR_t Exec(InquireDelay* IDelay)
    {
        uint16_t irk = 0; // 定义红外线按键值
        this->DispScore();
        do {
            // delay(1000);
            //  等待红外线接收到数据
            //  while (!mmhardware.irrecv.available()) delay(10);
            if (mmhardware.IRRCode(irk, true)) { // 读取红外线值
                switch (irk) {
                case IRK_UP:
                    ++NextScoreA;
                    break;
                case IRK_DOWN:
                    ++NextScoreB;
                    break;
                case IRK_LEFT:
                    --NextScoreA;
                    break;
                case IRK_RIGHT:
                    --NextScoreB;
                    break;
                case IRK_SET: // 长安Set键归零
                {
                    bool rset = true; // 默认重置
                    for (int i = 0; i < 10; ++i) { // 等待按键
                        // 如果仍然按着set键则等待
                        if (mmhardware.IRRCode(irk, true) && irk == IRK_SET) {
                            delay(100);
                        } else {
                            rset = false;
                            break;
                        }
                    }
                    if (rset) { // 如果需要重置分数
                        this->NextScoreA = 0;
                        this->NextScoreB = 0;
                    }
                } break;
                default:
                    break;
                }

                this->DispScoreChange();
            }
        } while (IDelay->IDelay(100));
        return EXECR_OK;
    }
};

#endif