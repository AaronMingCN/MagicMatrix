/**
 * @file MMCommand.hpp
 * @date 2024/03/14 23:25:45
 * @author Aaron Ming
 * @version 1.0
 * @brief 命令执行类
 * @details 用于执行通过串口或蓝牙传入的命令
 */

#ifndef _MMCOMMAND_HPP
#define _MMCOMMAND_HPP

#include "MMHardware.hpp"
#include "MMMenu.hpp"
#include <vector>

/// @brief 命令执行类
/// @details 根据命令字符串执行对应命令 \n
/// 命令格式：命令 参数1 参数2 ...
class MMCommand {
private:
public:
    // 将命令行分割
    void SplitCMD(String CMDString, std::vector<String>& vcmd)
    {
        String t;
        for (auto c : CMDString) {
            if (c == ' ' || c == '\0' || c == '\n' || c == '\r') { // 如果遇到空格或字符串结束
                t.trim(); // 去掉多余的空格
                if (t.length())
                    vcmd.push_back(t);
                t = "";
            } else
                t += c;
        }
        t.trim(); // 如果还有没处理完的数据则继续追加
        if (t.length())
            vcmd.push_back(t);
    }

    /// @brief 执行命令
    /// @param CMDString 命令行字符串
    /// @note 命令示例：\n
    /// MM MENU 0 0 \n
    /// MM SDT 2024 03 15 00 00 00
    void Exec(String CMDString);
} mmcommand;

/// @brief 执行命令
/// @param CMDString 命令行字符串
void MMCommand::Exec(String CMDString)
{
    std::vector<String> vcmd; // 定义分割后的命令
    this->SplitCMD(CMDString, vcmd);
    if (vcmd.size()) {
        if (vcmd[0] == "MM") {
            if (vcmd.size() > 1 && vcmd[1] == "HELP") { // 显示命令帮助
                UART_USB.println("---------- samples ----------");
                UART_USB.println("MM MENU 0 0");
                UART_USB.println("MM SDT 2024 03 15 00 00 00");
                UART_USB.println("-----------------------------");
            } else if (vcmd.size() > 3 && vcmd[1] == "MENU") { // 设置菜单位置格式: MM MENU 0 0
                mmmenu.NextMenuCate = vcmd[2].toInt();
                mmmenu.NextMenuItem = vcmd[3].toInt();
            } else if (vcmd.size() > 7 && vcmd[1] == "SDT") { // 设置时间格式: MM SDT 2024 03 15 00 00 00
                mmhardware.SetDateTime(vcmd[2].toInt(), vcmd[3].toInt(), vcmd[4].toInt(),
                    vcmd[5].toInt(), vcmd[6].toInt(), vcmd[7].toInt());
            }
        }
#ifdef MMDEBUG
        UART_USB.println("------------------");
        for (auto c : vcmd) {
            UART_USB.println("->" + c);
        }
#endif
    }
}

#endif
