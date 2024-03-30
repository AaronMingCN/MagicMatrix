/**
 * @file MMF_DispBmpLoop.hpp
 * @date 2024/02/26 13:39:43
 * @author
 * @version 1.0
 * @brief 循环播放bmp图片
 * @details 将bmp文件保存在sd卡中的bmp文件夹下循环播放
 */

#ifndef _MMF_DISPBMPLOOP_HPP
#define _MMF_DISPBMPLOOP_HPP

#include "../MMConfig.hpp"
#include "../MMFill.hpp"
#include "MMFunc.hpp"
#include "MMSD.hpp"
#include "MMScr.hpp"

/// @brief 显示周期最短时间
#define MMF_DBL_INTER_MIN 500

/// @brief 循环显示bmp静态图片
class MMF_DispBmpLoop : public MMFunc {
public:
    /// @brief 显示周期
    unsigned long Interval = 500;
    /// @brief 是否暂停中
    bool pause = false;

    /// @brief 构造函数
    /// @param fid 功能块ID
    MMF_DispBmpLoop(uint16_t fid)
        : MMFunc(fid)
    {
    }

    /// @brief 根据序号显示图片
    /// @param dir 路径
    /// @param Order 图片在路径中的序号
    void DrawBMPByOrder(File& dir, uint16_t Order)
    {
        mmsd.MoveToFileByOrder(dir, Order); // 跳转到文件位置
        File f = dir.openNextFile();
        if (f) {
            if (!f.isDirectory()) { // 如果不是文件夹
                mmsd.DrawBitmapFile(f); // 则将文件绘制
            }
            f.close();
        }
    }

    /// @brief 执行功能
    /// @param IDelay 等待询问接口
    /// @return 执行结果
    virtual MMFExecR_t Exec(InquireDelay* IDelay)
    {
        mmconfig.SaveIfNeeded(); // 避免显示时占用sd卡无法保存设置
        mmscr.FillAll(0xFF, 0xFF, 0xFF); // 填充空白
        mmscr.Update();
        mmsd.GetLockSD(); // 获得SD锁
        if (!SD.begin(PIN_SD_SS)) {
            UART_USB.println("initialization failed!");
            while (IDelay->IDelay(1000))
                ; // 如果打开失败则等待
        } else {
            UART_USB.println("initialization done.");
            File dir = SD.open("/bmp/"); // 打开SD卡中的bmp文件夹
            if (dir)
                do {

                    // this->DrawBMPByOrder(dir, 3);
                    // delay(3000);
                    // dir.rewindDirectory();

                    for (;;) { // 以此读取文件夹下的bmp文件
                        if (!this->pause) { // 如果没有暂停则显示下一个图片
                            File entry = dir.openNextFile();
                            if (entry) { // 如果文件打开成功
                                if (!entry.isDirectory()) { // 如果不是文件夹
                                    mmsd.DrawBitmapFile(entry); // 则将文件绘制
                                }
                                entry.close(); // 关闭文件
                            } else
                                break;
                        }
                        uint16_t IRRCode; // 如果读取到按键信息则
                        if (IDelay->IDelay(Interval, IRRCode, true)) {
                            switch (IRRCode) {
                            case IRK_UP: // 如果是上键增加等待500毫秒
                                this->Interval += 500;
                                delay(100);
                                break;
                                
                            case IRK_DOWN: // 如果是下键减少等待500毫秒
                                if (this->Interval > 500)
                                    this->Interval -= 500;
                                delay(100);
                                break;
                            case IRK_SET: // 如果是Set键切换暂停状态
                                this->pause = !this->pause;
                                delay(100);
                                break;
                            default:
                                // IDelay->IDelay(Interval, IRRCode, true);
                                delay(100);
                                break;
                            }
                        } else
                            break;
                    }
                    dir.rewindDirectory(); // 返回到文件夹首位置
                } while (IDelay->Inquire());
            // SD.end();
        }
        mmsd.ReleaseSD(); // 释放SD锁
        return EXECR_OK;
    }
};

#endif