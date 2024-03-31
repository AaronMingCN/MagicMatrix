/**
 * @file MMCharDefine.hpp
 * @date 2024/03/27 19:56:53
 * @author Aaron Ming
 * @version 1.0
 * @brief 字符点阵定义
 * @details 采用5x3的矩阵来显示字符
 */

#ifndef _MMCHARDEFINE_HPP
#define _MMCHARDEFINE_HPP

#define MMCHAR_WIDTH (3) ///< 定义字符的宽度
#define MMCHAR_HEIGHT (5) ///< 定义字符的高度

/// @brief 定义在绘制MM字符时的回调事件
/// @param x 相对横向值
/// @param y 相对纵向值
/// @param abx 绝对横向值
/// @param aby 绝对纵向值
/// @param rgb 用于绘制的颜色
typedef void (*OnDrawChar)(int16_t x, int16_t y, int16_t abx, int16_t aby, RGB& rgb);

/// @brief MMChar的字符样式类
class MMCStyle {
public:

    /// @brief 实现OnDrawChar
    static void MMCS_0(int16_t x, int16_t y, int16_t abx, int16_t aby, RGB& rgb)
    {
        rgb.R = 255;
        rgb.G = (y * 256 / MMCHAR_HEIGHT);
        rgb.B = 0;
    }  

    /// @brief 实现OnDrawChar
    static void MMCS_1(int16_t x, int16_t y, int16_t abx, int16_t aby, RGB& rgb)
    {
        rgb.R = 255 - (y * 256 / MMCHAR_HEIGHT);
        rgb.G = (y * 256 / MMCHAR_HEIGHT);
        rgb.B = 255;
    }

    /// @brief 实现OnDrawChar
    static void MMCS_2(int16_t x, int16_t y, int16_t abx, int16_t aby, RGB& rgb)
    {
        rgb.R = 255 - (y * 256 / MMCHAR_HEIGHT);
        rgb.G = 255;
        rgb.B = (y * 256 / MMCHAR_HEIGHT);
    }

    /// @brief 实现OnDrawChar
    static void MMCS_3(int16_t x, int16_t y, int16_t abx, int16_t aby, RGB& rgb)
    {
        rgb.R = 255;
        rgb.G = 255 - (y * 256 / MMCHAR_HEIGHT);
        rgb.B = (y * 256 / MMCHAR_HEIGHT);
    }

    /// @brief 实现OnDrawChar
    static void MMCS_4(int16_t x, int16_t y, int16_t abx, int16_t aby, RGB& rgb)
    {
        rgb.R = (y * 256 / MMCHAR_HEIGHT);
        rgb.G = 255;
        rgb.B = 255 - (y * 256 / MMCHAR_HEIGHT);
    }    
    /// @brief 实现OnDrawChar
    static void MMCS_5(int16_t x, int16_t y, int16_t abx, int16_t aby, RGB& rgb)
    {
        rgb.R = 255;
        rgb.G = 255 - (y * 256 / MMCHAR_HEIGHT);
        rgb.B = 0;
    }      
    static OnDrawChar Styles[];
};

/// @brief 初始化样式列表，将样式添加到列表中
/// @details 使用时通过下标获得函数指针，然后将参数传递给MMGrap的绘制方法使用
OnDrawChar MMCStyle::Styles[] = {MMCS_0, MMCS_1, MMCS_2, MMCS_3, MMCS_4, MMCS_5 };

/// 定义字符空格的字符显示
#define CHAR_SPAC (0b0\
000\
000\
000\
000\
000)

/// 定义字符填充的字符显示
#define CHAR_FILL (0b0\
111\
111\
111\
111\
111)

/// 定义字符0的字符显示
#define CHAR_0 (0b0\
111\
101\
101\
101\
111)

/// 定义字符1的字符显示
#define CHAR_1 (0b0\
001\
001\
001\
001\
001)

/// 定义字符2的字符显示
#define CHAR_2 (0b0\
111\
001\
111\
100\
111)

/// 定义字符3的字符显示
#define CHAR_3 (0b0\
111\
001\
111\
001\
111)

/// 定义字符4的字符显示
#define CHAR_4 (0b0\
101\
101\
111\
001\
001)

/// 定义字符5的字符显示
#define CHAR_5 (0b0\
111\
100\
111\
001\
111)

/// 定义字符6的字符显示
#define CHAR_6 (0b0\
111\
100\
111\
101\
111)

/// 定义字符7的字符显示
#define CHAR_7 (0b0\
111\
001\
001\
001\
001)

/// 定义字符8的字符显示
#define CHAR_8 (0b0\
111\
101\
111\
101\
111)

/// 定义字符9的字符显示
#define CHAR_9 (0b0\
111\
101\
111\
001\
111)

/// 定义字符.的字符显示
#define CHAR_DOT (0b0\
000\
000\
000\
000\
100)

/// 定义字符+的字符显示
#define CHAR_PLUS (0b0\
000\
010\
111\
010\
000)

/// 定义字符-的字符显示
#define CHAR_MINU (0b0\
000\
000\
111\
000\
000)

/// 定义字符A的字符显示
#define CHAR_A (0b0\
111\
101\
111\
101\
101)

/// 定义字符B的字符显示
#define CHAR_B (0b0\
100\
100\
111\
101\
111)

/// 定义字符C的字符显示
#define CHAR_C (0b0\
111\
100\
100\
100\
111)

/// 定义字符D的字符显示
#define CHAR_D (0b0\
001\
001\
111\
101\
111)

/// 定义字符E的字符显示
#define CHAR_E (0b0\
111\
100\
111\
100\
111)

/// 定义字符F的字符显示
#define CHAR_F (0b0\
111\
100\
111\
100\
100)

/// 定义字符G的字符显示
#define CHAR_G (0b0\
111\
100\
101\
101\
111)

/// 定义字符H的字符显示
#define CHAR_G (0b0\
101\
101\
111\
101\
101)

/// 定义字符I的字符显示
#define CHAR_I (0b0\
111\
010\
010\
010\
111)

/// 定义字符P的字符显示
#define CHAR_P (0b0\
111\
101\
111\
100\
100)

/// 定义字符%的字符显示
#define CHAR_PERC (0b0\
101\
001\
010\
100\
101)

#endif