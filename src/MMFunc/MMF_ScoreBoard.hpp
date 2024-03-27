/**
 * @file MMF_ScoreBoard.hpp
 * @date 2024/02/29 22:45:38
 * @author Aaron Ming 
 * @version 1.0
 * @brief 记分牌
 * @details 
 */


#ifndef _MMF_SCOREBOARD_HPP
#define _MMF_SCOREBOARD_HPP

#include "../MMFill.hpp"
#include "MMFunc.hpp"
// #include "MMScr.hpp"


/// @brief 记分牌功能
class MMF_ScoreBoard : public MMFunc {
public:
    /// @brief 当前分数A
    /// @details 避免重复绘制分数消耗资源
    int CurrScoreA = 0; 
    /// @brief 当前分数B
    int CurrScoreB = 0;
    /// @brief 下一个分数A
    int NextScoreA = 0; 
    /// @brief 下一个分数B
    int NextScoreB = 0;

    /// @brief 构造函数
    /// @param fid 当前功能ID    
    MMF_ScoreBoard(uint16_t fid)
        : MMFunc(fid)
    {
    }

    /// @brief 显示分数
    void DispScore()
    {
        char buff[5] = {}; // 用于保存格式化后字符串的缓存
        mmhardware.matrix.clear();
        mmhardware.matrix.setCursor(-1, 0);
        mmhardware.matrix.setTextColor(mmhardware.matrix.Color(255, 0, 0));
        sprintf(buff, "%3d", CurrScoreA);
        mmhardware.matrix.print(buff);
        mmhardware.matrix.setCursor(-1, 9);
        mmhardware.matrix.setTextColor(mmhardware.matrix.Color(0, 255, 0));
        sprintf(buff, "%3d", CurrScoreB);
        mmhardware.matrix.print(buff);
        mmhardware.matrix.show();
    }


    /// @brief 如果改变了则绘制
    /// @return 是否完成了绘制
    bool DispScoreChange()
    {
        bool r = false;
        // 如果分数发生改变则开始绘图
        if ((CurrScoreA != NextScoreA) || (CurrScoreB != NextScoreB)) {
            CurrScoreA = NextScoreA;
            CurrScoreB = NextScoreB;
            r = true;
            this->DispScore();
        }
        return r;
    }

    /// @brief 执行功能
    /// @param IDelay 询问等待接口
    /// @return 执行结果   
    virtual MMFExecR_t Exec(InquireDelay* IDelay)
    {
        uint16_t irk = 0; // 定义红外线按键值
        this->DispScore();
        while (IDelay->Inquire(irk)) {
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
            // 如果修改了分数则更新显示并等待
            if (this->DispScoreChange()) {
                IDelay->IDelay(200, irk);
            }
        }

        return EXECR_OK;
    }
};

#endif