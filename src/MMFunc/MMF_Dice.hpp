/*
 * @File :  MMF_Dice.hpp
 * @Time :  2024/03/05 14:30:13
 * @Auth :
 * @Vers :  1.0
 * @Desc :  投骰子
 */

#ifndef _MMF_DICE_HPP
#define _MMF_DICE_HPP

#include "../MMFill.hpp"
#include "MMFunc.hpp"
#include "MMScr.hpp"

// 投骰子游戏
// 向上1个，向左2两个，向下三个，向右4个
class MMF_Dice : public MMFunc {
public:
    MMF_Dice(uint16_t fid)
        : MMFunc(fid)
    {
        randomSeed(analogRead(0)); // 初始化随机种子
    }

    // 投1个骰子
    void Dice_1() {
        uint8_t r = random(1, 7); // 取1~6的随机数
        mmhardware.matrix.clear();
        mmhardware.matrix.setTextSize(2);
        mmhardware.matrix.setTextColor(RGB::Color(0, 255, 255));        
        mmhardware.matrix.setCursor(3,1);
        mmhardware.matrix.print(r);
        mmhardware.matrix.show();
        mmhardware.matrix.setTextSize(1);
    }

    // 投2个骰子
    void Dice_2() {
        uint8_t r = random(1, 7); // 取1~6的随机数
        uint8_t r1 = random(1, 7); // 取1~6的随机数
        mmhardware.matrix.clear();
        mmhardware.matrix.setTextSize(1);
        mmhardware.matrix.setTextColor(RGB::Color(255, 255, 0));        
        mmhardware.matrix.setCursor(3,0);
        mmhardware.matrix.print(r);

        mmhardware.matrix.setTextColor(RGB::Color(255, 0, 255));        
        mmhardware.matrix.setCursor(8,9);
        mmhardware.matrix.print(r1);

        mmhardware.matrix.show();

    }

    // 投3个骰子
    void Dice_3() {
        uint8_t r = random(1, 7); // 取1~6的随机数
        uint8_t r1 = random(1, 7); // 取1~6的随机数
        uint8_t r2 = random(1, 7); // 取1~6的随机数
        mmhardware.matrix.clear();
        mmhardware.matrix.setTextSize(1);
        mmhardware.matrix.setTextColor(RGB::Color(255, 0, 0));        
        mmhardware.matrix.setCursor(5,0);
        mmhardware.matrix.print(r);

        mmhardware.matrix.setTextColor(RGB::Color(0, 255, 0));        
        mmhardware.matrix.setCursor(2,9);
        mmhardware.matrix.print(r1);

        mmhardware.matrix.setTextColor(RGB::Color(0, 0, 255));        
        mmhardware.matrix.setCursor(9,9);
        mmhardware.matrix.print(r2);
        
        mmhardware.matrix.show();

    }

    // 投3个骰子
    void Dice_4() {
        uint8_t r = random(1, 7); // 取1~6的随机数
        uint8_t r1 = random(1, 7); // 取1~6的随机数
        uint8_t r2 = random(1, 7); // 取1~6的随机数
        uint8_t r3 = random(1, 7); // 取1~6的随机数        
        mmhardware.matrix.clear();
        mmhardware.matrix.setTextSize(1);
        mmhardware.matrix.setTextColor(RGB::Color(255, 255, 0));        
        mmhardware.matrix.setCursor(2,0);
        mmhardware.matrix.print(r);

        mmhardware.matrix.setTextColor(RGB::Color(0, 255, 255));        
        mmhardware.matrix.setCursor(9,0);
        mmhardware.matrix.print(r1);

        mmhardware.matrix.setTextColor(RGB::Color(0, 0, 255));        
        mmhardware.matrix.setCursor(2,9);
        mmhardware.matrix.print(r2);

        mmhardware.matrix.setTextColor(RGB::Color(255, 0, 255));        
        mmhardware.matrix.setCursor(9,9);
        mmhardware.matrix.print(r3);        
        
        mmhardware.matrix.show();

    }


    virtual MMFExecR_t Exec(InquireDelay* IDelay)
    {
        uint16_t irk = 0; // 定义红外线按键值
        this->Dice_1();
        do {
            if (mmhardware.IRRCode(irk, true)) { // 读取红外线值
                switch (irk) {
                case IRK_UP:
                    this->Dice_1();
                    break;
                case IRK_LEFT:
                    this->Dice_2();
                    break;
                case IRK_DOWN:
                    this->Dice_3();
                    break;
                case IRK_RIGHT:
                    this->Dice_4();                
                    break;
                default:
                    break;
                }
            }
        } while (IDelay->IDelay(100));
        return EXECR_OK;
    }
};

#endif