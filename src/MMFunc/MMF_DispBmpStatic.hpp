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

/// @brief 矩阵屏幕测试类，测试RGB显示
class MMF_DispBmpStatic : public MMFunc {
public:
    /// @brief 构造函数
    /// @param fid 当前功能ID
    MMF_DispBmpStatic(uint16_t fid)
        : MMFunc(fid)
    {
        
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