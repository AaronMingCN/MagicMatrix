/*
 * @File :  MMF_DispBmpLoop.hpp
 * @Time :  2024/02/26 13:39:43
 * @Auth :
 * @Vers :  1.0
 * @Desc :  循环播放bmp图片
 */

#ifndef _MMF_DISPBMPLOOP_HPP
#define _MMF_DISPBMPLOOP_HPP

#include "../MMFill.hpp"
#include "MMFunc.hpp"
#include "MMSD.hpp"
#include "MMScr.hpp"
#include "../MMConfig.hpp"

// 循环显示bmp静态图片
class MMF_DispBmpLoop : public MMFunc {
public:
    MMF_DispBmpLoop(uint16_t fid)
        : MMFunc(fid)
    {
    }


    virtual MMFExecR_t Exec(InquireDelay* IDelay)
    {
        mmscr.Fill(0xFF, 0xFF, 0xFF); // 填充空白
        mmscr.Update();
        mmsd.GetLockSD(); // 获得SD锁
        if  (!SD.begin(PIN_SD_SS)) {
            UART_USB.println("initialization failed!");
            while (IDelay->IDelay(1000)); // 如果打开失败则等待
        } else {
            UART_USB.println("initialization done.");
            File dir = SD.open("/bmp/"); // 打开SD卡中的bmp文件夹
            do {
                do { // 以此读取文件夹下的bmp文件
                    File entry = dir.openNextFile();
                    if (entry) { // 如果文件打开成功
                        if (!entry.isDirectory()) { // 如果不是文件夹
                            mmsd.DrawBitmapFile(entry); // 则将文件绘制
                        }
                        entry.close(); // 关闭文件
                    } else
                        break;
                } while (IDelay->IDelay(1000));
                dir.rewindDirectory(); // 返回到文件夹首位置
            } while (IDelay->Inquire());
            // SD.end();
        }
        mmsd.ReleaseSD(); // 释放SD锁
        return EXECR_OK;
    }
};

#endif