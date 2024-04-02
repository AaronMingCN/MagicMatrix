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

/// @brief 矩阵屏幕测试类，测试RGB显示
class MMF_DispBmpStatic : public MMFunc {
public:
    /// @brief 构造函数
    /// @param fid 当前功能ID
    MMF_DispBmpStatic(uint16_t fid)
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
    /// @param IDelay 询问等待接口
    /// @return 执行结果
    virtual MMFExecR_t Exec(InquireDelay* IDelay)
    {
        if (IDelay->Inquire()) {
            mmscr.FillAll(255, 0, 0);
            mmscr.Update();
            if (IDelay->IDelay(500)) {
                mmscr.FillAll(0, 255, 0);
                mmscr.Update();
            }
            if (IDelay->IDelay(500)) {
                mmscr.FillAll(0, 0, 255);
                mmscr.Update();
            }
            if (IDelay->IDelay(500)) {
                mmscr.SetEmpty();
                mmscr.Update();
            }
        }
        return EXECR_OK;
    }
};

#endif