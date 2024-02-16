/*
 * @File :  MMFill.hpp
 * @Time :  2024/02/13 10:35:57
 * @Vers :  1.0
 * @Desc :  矩阵屏幕相关的填充功能
 */

#ifndef _MMFILL_HPP
#define _MMFILL_HPP

// 填充相关
#include "MMDefine.hpp"
#include "MMScr.hpp"

class MMFill {
public:
    // 根据屏幕逻辑顺序，测试每一个像素点
    void PixTestLogicalOrder()
    {
        for (int i = 0; i < M_HEIGHT; ++i) { // 将所有颜色清空
            for (int j = 0; j < M_WIDTH; ++j) {
                mmscr.SetPixel(j, i, 255, 255, 255);
                mmscr.Update();
                mmscr.SetEmpty();
            }
        }
        delay(100);
        mmscr.Clear();
    }

    // 根据屏幕物理顺序，测试每一个像素点
    void PixTestPhysicalOrder()
    {
        for(uint16_t i = 0; i < M_PIXS; ++i) {
            matrix.setPixelColor(i, 255, 255, 255);
        }
        delay(100);
        mmscr.Clear();
    }


    // 行填充
    void RowFill()
    {
        for (int i = 0; i < M_HEIGHT; ++i) { // 将所有颜色清空
            for (int j = 0; j < M_WIDTH; ++j) {
                mmscr.SetPixel(j, i, 255, (i * 255 / M_WIDTH), 0);
            }
            delay(100);
            mmscr.Update();
        }
        mmscr.Clear();
    }

    // 列填充
    void ColFill()
    {
        for (int j = 0; j < M_WIDTH; ++j) {
            for (int i = 0; i < M_HEIGHT; ++i) {
                mmscr.SetPixel(j, i, 255, (i * 255 / M_WIDTH), 0);
            }
            delay(100);
            mmscr.Update();
        }
        mmscr.SetEmpty();
    }

    // 对角线填充
    void DiagFill()
    {
        for (int i = 0; i < M_WIDTH; ++i) {
            int r = i, c = i;
            while (r < M_HEIGHT && c >= 0) {
                mmscr.SetPixel(c, r, 255, (i * 255 / M_WIDTH), 0);
                ++r, --c;
            }
            r = i, c = i;
            while (r >= 0 && c < M_WIDTH) {
                mmscr.SetPixel(c, r, 255, (i * 255 / M_WIDTH), 0);
                --r, ++c;
            }
            delay(100);
            mmscr.Update();
        }
        mmscr.SetEmpty();
    }

    // 对角线填充
    void DiagFill_1()
    {
        for (int i = 0; i < M_HEIGHT; ++i) {
            int r = i, c = 0;
            while (r >= 0) {
                mmscr.SetPixel(c, r, 255, (r * 255 / M_HEIGHT), (c * 255 / M_WIDTH));
                --r, ++c;
            }
            delay(50);
            mmscr.Update();
        }

        for (int i = 0; i < M_WIDTH; ++i) {
            int r = M_HEIGHT, c = i;
            while (c < M_WIDTH) {
                mmscr.SetPixel(c, r, 255, (r * 255 / M_HEIGHT), (c * 255 / M_WIDTH));
                --r, ++c;
            }
            delay(50);
            mmscr.Update();
        }
        mmscr.SetEmpty();
    }

    // 蛇形填充
    void SnakeFill()
    {
        for (int i = 0; i < M_HEIGHT; ++i) { // 行循环
            if (i % 2)
                for (int j = M_WIDTH - 1; j >= 0; --j) {
                    mmscr.SetPixel(j, i, 255, (i * 255 / M_HEIGHT), (j * 255 / M_WIDTH));
                    mmscr.Update();
                    delay(10);
                }
            else
                for (int j = 0; j < M_WIDTH; ++j) {
                    mmscr.SetPixel(j, i, 255, (i * 255 / M_HEIGHT), (j * 255 / M_WIDTH));
                    mmscr.Update();
                    delay(10);
                }
        }
        mmscr.SetEmpty();
    }

    // 矩形填充
    void RectFill()
    {
        for (int i = 0; i < M_HEIGHT / 2; ++i) {
            for (int j = i; j < M_WIDTH - i; ++j)
                mmscr.SetPixel(j, i, 255, (i * 255 / M_HEIGHT), (j * 255 / M_WIDTH));
            for (int j = i; j < M_HEIGHT - i; ++j)
                mmscr.SetPixel(i, j, 255, (i * 255 / M_HEIGHT), (j * 255 / M_WIDTH));
            for (int j = (M_WIDTH - i - 1); j >= i; --j)
                mmscr.SetPixel(j, M_HEIGHT - i - 1, 255, (i * 255 / M_HEIGHT), (j * 255 / M_WIDTH));
            for (int j = (M_HEIGHT - i - 1); j >= i; --j)
                mmscr.SetPixel(M_HEIGHT - i - 1, j, 255, (i * 255 / M_HEIGHT), (j * 255 / M_WIDTH));
            mmscr.Update();
            delay(200);
        }
        matrix.clear();
    }

    // 彩虹
    void Rainbow()
    {
        matrix.rainbow();
        matrix.show();
    }

    // 测试矩阵
    void MatrixTest()
    {
        mmscr.Fill(255, 0, 0);
        mmscr.Update();
        delay(500);
        mmscr.Fill(0, 255, 0);
        mmscr.Update();
        delay(500);
        mmscr.Fill(0, 0, 255);
        mmscr.Update();
        delay(500);
        mmscr.SetEmpty();
        mmscr.Update();
    }

    // 警灯闪烁
    void AlarmLamp()
    {
        for (uint8_t i = 0; i < 10; ++i) {
            mmscr.Fill(255, 0, 0);
            mmscr.Update();
            delay(100);
            mmscr.Fill(0, 0, 255);
            mmscr.Update();
            delay(100);
        }
    }

} mmfill;

#endif