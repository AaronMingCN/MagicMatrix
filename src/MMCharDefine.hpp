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

#include <map>
#include <vector>

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

    /// @brief 实现OnDrawChar
    static void MMCS_6(int16_t x, int16_t y, int16_t abx, int16_t aby, RGB& rgb)
    {
        rgb.R = 255 - (y * 256 / MMCHAR_HEIGHT);
        rgb.G = 255;
        rgb.B = (y * 256 / MMCHAR_HEIGHT);
    }
    static OnDrawChar Styles[];
};

/// @brief 初始化样式列表，将样式添加到列表中
/// @details 使用时通过下标获得函数指针，然后将参数传递给MMGrap的绘制方法使用
OnDrawChar MMCStyle::Styles[] = { MMCS_0, MMCS_1, MMCS_2, MMCS_3, MMCS_4, MMCS_5, MMCS_6 };

/// 定义字符空格的字符显示
#define MMCHAR_SPAC (0b0\
000\
000\
000\
000\
000)

/// 定义字符填充的字符显示
#define MMCHAR_FILL (0b0\
111\
111\
111\
111\
111)

/// 定义字符0的字符显示
#define MMCHAR_0 (0b0\
111\
101\
101\
101\
111)

/// 定义字符1的字符显示
#define MMCHAR_1 (0b0\
001\
001\
001\
001\
001)

/// 定义字符2的字符显示
#define MMCHAR_2 (0b0\
111\
001\
111\
100\
111)

/// 定义字符3的字符显示
#define MMCHAR_3 (0b0\
111\
001\
111\
001\
111)

/// 定义字符4的字符显示
#define MMCHAR_4 (0b0\
101\
101\
111\
001\
001)

/// 定义字符5的字符显示
#define MMCHAR_5 (0b0\
111\
100\
111\
001\
111)

/// 定义字符6的字符显示
#define MMCHAR_6 (0b0\
111\
100\
111\
101\
111)

/// 定义字符7的字符显示
#define MMCHAR_7 (0b0\
111\
001\
001\
001\
001)

/// 定义字符8的字符显示
#define MMCHAR_8 (0b0\
111\
101\
111\
101\
111)

/// 定义字符9的字符显示
#define MMCHAR_9 (0b0\
111\
101\
111\
001\
111)

/// 定义字符.的字符显示
#define MMCHAR_DOT (0b0\
000\
000\
000\
000\
100)

/// 定义字符+的字符显示
#define MMCHAR_PLUS (0b0\
000\
010\
111\
010\
000)

/// 定义字符-的字符显示
#define MMCHAR_MINU (0b0\
000\
000\
111\
000\
000)

/// 定义字符A的字符显示
#define MMCHAR_A (0b0\
010\
101\
111\
101\
101)

/// 定义字符B的字符显示
#define MMCHAR_B (0b0\
110\
101\
110\
101\
110)

/// 定义字符C的字符显示
#define MMCHAR_C (0b0\
011\
100\
100\
100\
011)

/// 定义字符D的字符显示
#define MMCHAR_D (0b0\
110\
101\
101\
101\
110)

/// 定义字符E的字符显示
#define MMCHAR_E (0b0\
111\
100\
111\
100\
111)

/// 定义字符F的字符显示
#define MMCHAR_F (0b0\
111\
100\
111\
100\
100)

/// 定义字符G的字符显示
#define MMCHAR_G (0b0\
011\
100\
100\
101\
011)

/// 定义字符H的字符显示
#define MMCHAR_H (0b0\
101\
101\
111\
101\
101)

/// 定义字符I的字符显示
#define MMCHAR_I (0b0\
111\
010\
010\
010\
111)

/// 定义字符I的字符显示
#define MMCHAR_J (0b0\
001\
001\
001\
101\
010)

/// 定义字符I的字符显示
#define MMCHAR_K (0b0\
100\
101\
110\
110\
101)

/// 定义字符L的字符显示
#define MMCHAR_L (0b0\
100\
100\
100\
100\
111)

/// 定义字符P的字符显示
#define MMCHAR_P (0b0\
110\
101\
110\
100\
100)

/// 定义字符Q的字符显示
#define MMCHAR_Q (0b0\
010\
101\
101\
010\
001)

/// 定义字符R的字符显示
#define MMCHAR_R (0b0\
110\
101\
110\
110\
101)

/// 定义字符S的字符显示
#define MMCHAR_S (0b0\
011\
100\
010\
001\
110)

/// 定义字符T的字符显示
#define MMCHAR_T (0b0\
111\
010\
010\
010\
010)

/// 定义字符%的字符显示
#define MMCHAR_PERC (0b0\
101\
001\
010\
100\
101)

/// 定义字符:的字符显示
#define MMCHAR_COLON (0b0\
000\
100\
000\
100\
000)

/// 定义两点横线
#define MMCHAR_SHORTMINUS (0b0\
000\
000\
110\
000\
000)

/// 定义>字符
#define MMCHAR_MORE (0b0\
100\
010\
001\
010\
100)

/// 定义<字符
#define MMCHAR_LESS (0b0\
001\
010\
100\
010\
001)

/// 定义=字符
#define MMCHAR_EQUAL (0b0\
000\
111\
000\
111\
000)

/// @brief 字符集类
class MMCharset {
public:
    /// @brief 定义字符集，通过值获得
    std::map<char, uint16_t> Items;
    /// @brief 构造函数，将字符像素值加入字符集
    MMCharset()
    {
        SetVal(' ', MMCHAR_SPAC); // 加入空格
        SetVal(0, MMCHAR_FILL); // 加入填充，ascii值为0时
        SetVal('0', MMCHAR_0);
        SetVal('1', MMCHAR_1);
        SetVal('2', MMCHAR_2);
        SetVal('3', MMCHAR_3);
        SetVal('4', MMCHAR_4);
        SetVal('5', MMCHAR_5);
        SetVal('6', MMCHAR_6);
        SetVal('7', MMCHAR_7);
        SetVal('8', MMCHAR_8);
        SetVal('9', MMCHAR_9);
        SetVal('.', MMCHAR_DOT);
        SetVal('+', MMCHAR_PLUS);
        SetVal('-', MMCHAR_MINU);
        SetVal('A', MMCHAR_A);
        SetVal('B', MMCHAR_B);
        SetVal('C', MMCHAR_C);
        SetVal('D', MMCHAR_D);
        SetVal('E', MMCHAR_E);
        SetVal('F', MMCHAR_F);
        SetVal('G', MMCHAR_G);
        SetVal('H', MMCHAR_H);
        SetVal('I', MMCHAR_I);
        SetVal('J', MMCHAR_J);
        SetVal('K', MMCHAR_K);
        SetVal('L', MMCHAR_L);
        SetVal('P', MMCHAR_P);
        SetVal('Q', MMCHAR_Q);
        SetVal('R', MMCHAR_R);
        SetVal('S', MMCHAR_S);
        SetVal('T', MMCHAR_T);        
        SetVal('%', MMCHAR_PERC);
        SetVal(':', MMCHAR_COLON);
        SetVal('>', MMCHAR_MORE);
        SetVal('<', MMCHAR_LESS);
        SetVal('=', MMCHAR_EQUAL);
    }

    /// @brief 设置字符值
    /// @param c 字符
    /// @param val 值
    void SetVal(char c, uint16_t val)
    {
        // this->Items.insert(std::pair<char, uint16_t>(c, val));
        this->Items[c] = val;
    }

    /// @brief 获得字符值
    /// @param c 字符
    /// @param Default 默认值，如果没有找到则返回该值
    /// @return 如果存在则返回字符值，否则返回
    uint16_t GetVal(char c, uint16_t Default = MMCHAR_FILL)
    {
        uint16_t r = Default; // 默认为全部填充
        std::map<char, uint16_t>::iterator it = this->Items.find(c);
        if (it != this->Items.end()) {
            r = it->second;
        }
        return r;
    }
} mmcharset;

#endif