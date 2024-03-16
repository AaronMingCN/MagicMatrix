/*
 * @File :  MMCommand.hpp
 * @Time :  2024/03/14 23:25:45
 * @Auth :
 * @Vers :  1.0
 * @Desc :  命令执行类
 */

#ifndef _MMCOMMAND_HPP
#define _MMCOMMAND_HPP

#include "MMHardware.hpp"
#include "MMMenu.hpp"
#include <vector>

// 命令执行类，根据命令字符串执行对应命令
// 命令格式：命令 参数1 参数2 ...
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
        if (t.length()) vcmd.push_back(t);
    }

    // 执行命令行
    void Exec(String CMDString);
} mmcommand;

// 执行命令
void MMCommand::Exec(String CMDString)
{
    std::vector<String> vcmd; // 定义分割后的命令
    this->SplitCMD(CMDString, vcmd);
    if (vcmd.size()) {
        if (vcmd[0] == "MM") {
            if (vcmd.size() >= 4 && vcmd[1] == "MENU") { // 设置菜单位置格式: MM MENU 0 0
                mmmenu.NextMenuCate = vcmd[2].toInt();
                mmmenu.NextMenuItem = vcmd[3].toInt();
            } else if (vcmd.size() >= 8 && vcmd[1] == "SDT") { // 设置时间格式: MM SDT 2024 03 15 00 00 00
                mmhardware.SetDateTime(vcmd[2].toInt(), vcmd[3].toInt(), vcmd[4].toInt(), 
                                       vcmd[5].toInt(), vcmd[6].toInt(), vcmd[7].toInt());
            }
        }
        UART_USB.println("------------------");
        for (auto c : vcmd) {
            UART_USB.println("->" + c);
        }
    }
}

#endif
