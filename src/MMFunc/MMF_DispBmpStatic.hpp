/**
 * @file MMF_DispBmpStatic.hpp
 * @date 2024/04/01 22:18:57
 * @author
 * @version 1.0
 * @brief 显示静态图片
 * @details None
 */

#ifndef _MMF_DISPBMPSTATIC_HPP
#define _MMF_DISPBMPSTATIC_HPP

#include "../MMSD.hpp"

/// @brief 静态显示BMP图片
class MMF_DispBmpStatic : public MMFunc {
public:
    /// @brief 当前显示的图片顺序
    uint16_t CurrOrder = 0;
    /// @brief 下一个需要显示的顺序
    uint16_t NextOrder = 0;

    /// @brief 构造函数
    /// @param fid 当前功能ID
    MMF_DispBmpStatic(uint16_t fid)
        : MMFunc(fid)
    {
    }

    /// @brief 根据序号显示图片
    /// @param Order 图片在路径中的序号
    /// @return 是否绘制成功
    bool DrawBMPByOrder(uint16_t Order)
    {
        bool r = false;
        mmsd.GetLockSD(); // 获得SD锁
        if (!SD.begin(PIN_SD_SS)) {
            UART_USB.println("initialization failed!");
        } else {
            UART_USB.println("initialization done.");
            File dir = SD.open(DIR_BMPSTATIC); // 打开SD卡中的bmp文件夹
            if (dir) {
                mmsd.MoveToFileByOrder(dir, Order); // 跳转到文件位置
                File f = dir.openNextFile();
                if (f) {
                    r = mmsd.DrawBitmapFile(f); // 则将文件绘制
                    f.close();
                }
            } else
                UART_USB.println("DIR_BMPSTATIC open failed!");
        }
        mmsd.ReleaseSD(); // 释放SD锁
        return r;
    }

    /// @brief 获得文件数量
    /// @return 文件的数量
    uint16_t GetFileCount()
    {
        uint16_t r = 0;
        mmsd.GetLockSD(); // 获得SD锁
        if (!SD.begin(PIN_SD_SS)) {
            UART_USB.println("initialization failed!");
        } else {
            UART_USB.println("initialization done.");
            File dir = SD.open(DIR_BMPSTATIC); // 打开SD卡中的bmp文件夹
            if (dir) {
                r = mmsd.FileCount(dir);
            } else
                UART_USB.println("DIR_BMPSTATIC open failed!");
        }
        mmsd.ReleaseSD(); // 释放SD锁
        return r;
    }

    /// @brief 执行功能
    /// @param IDelay 询问等待接口
    /// @return 执行结果
    virtual MMFExecR_t Exec(InquireDelay* IDelay)
    {
        mmconfig.SaveIfNeeded(); // 避免显示时占用sd卡无法保存设置
        mmscr.FillAll(0xFF, 0xFF, 0xFF); // 填充空白
        mmscr.Update();

        uint16_t FileCount = this->GetFileCount(); // 统计文件的个数
        uint16_t IRRCode = IRK_NONE; // 如果读取到按键信息则
        this->DrawBMPByOrder(this->CurrOrder);
        while (IDelay->Inquire(IRRCode)) { // 以此读取文件夹下的bmp文件
            if (this->CurrOrder != this->NextOrder) { // 避免重复绘制
                this->CurrOrder = this->NextOrder;
                this->DrawBMPByOrder(this->CurrOrder);
                mmconfig.Config[CFG_DISPBMPIDX] = this->CurrOrder; // 将当前序号写入配置
                mmconfig.NeedSave = true; // 标记需要保存配置
            }

            switch (IRRCode) {
            case IRK_RIGHT: // 如果是右键增加等待增加序号
                if (this->NextOrder < FileCount - 1)
                    ++(this->NextOrder);
                else
                    this->NextOrder = 0;
                IDelay->IDelay(IRR_WAITKEYTUP, IRRCode);
                break;

            case IRK_LEFT: // 如果是左键减少序号
                if (this->NextOrder > 0)
                    --(this->NextOrder);
                else
                    this->NextOrder = FileCount - 1;
                IDelay->IDelay(IRR_WAITKEYTUP, IRRCode);
                break;
            }
            IRRCode = IRK_NONE; // 接受完毕后必须重置IRRCode
        }

        return EXECR_OK;
    }
};

#endif