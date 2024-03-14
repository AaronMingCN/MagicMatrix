/*
 * @File :  MMCommand.hpp
 * @Time :  2024/03/14 23:25:45
 * @Auth :
 * @Vers :  1.0
 * @Desc :  命令执行类
 */

#ifndef _MMCOMMAND_HPP
#define _MMCOMMAND_HPP

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
    }

    // 执行命令行
    void Exec(String CMDString)
    {
        std::vector<String> vcmd; // 定义分割后的命令
        this->SplitCMD(CMDString, vcmd);
        for (auto c: vcmd) {
            UART_USB.println("->" + c);
        }
    }
} mmcommand;

#endif
