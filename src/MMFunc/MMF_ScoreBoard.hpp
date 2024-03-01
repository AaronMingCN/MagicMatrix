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
    MMF_ScoreBoard(uint16_t fid)
        : MMFunc(fid)
    {
        
    }
    virtual MMFExecR_t Exec(InquireDelay* IDelay)
    {
        if (IDelay->Inquire()) {
            mmscr.Fill(255, 0, 0);
            mmscr.Update();
            if (IDelay->IDelay(500)) {
                mmscr.Fill(0, 255, 0);
                mmscr.Update();
            }
            if (IDelay->IDelay(500)) {
                mmscr.Fill(0, 0, 255);
                mmscr.Update();
            }
            if (IDelay->IDelay(500)) {
                mmscr.SetEmpty();
                mmscr.Update();
            }
        }
        return EXECR_OK;
    }
};

#endif