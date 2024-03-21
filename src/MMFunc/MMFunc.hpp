/*
 * @File :  MMFunc.hpp
 * @Time :  2024/02/14 22:52:50
 * @Auth :
 * @Vers :  1.0
 * @Desc :  功能块的基础类用于派生功能
 */

#ifndef _MMFUNC_HPP
#define _MMFUNC_HPP

// 定义处理的结果默认为两个字节

/// @brief 执行结果 OK
#define EXECR_OK (0x0000)
#define EXECR_ERROR (0x0001) /// @brief 执行结果 ERROR

/// @brief 定义功能ID类型
typedef uint16_t MMFID_t;

/// @brief 定义功能type类型
typedef uint8_t MMFType_t;

/// @brief 定义功能执行结果类型
typedef uint16_t MMFExecR_t;

/// @brief 查询等待类型(接口)
/// @details
/// 在执行过程中询问是否需继续执行当前功能,用于响应退出操作
/// @note
/// + 返回为false是需要退出
/// + 传入的参数是等待的毫秒数,在功能块中应当使用IDelay替代delay()并对返回结果作出响应
/// + 询问等待的时间当不需要继续执行时可能不传入的时间短
class InquireDelay {
public:
    /// @brief 询问是否继续执行
    /// @return true允许，false不允许
    virtual bool Inquire()
    {
        return true;
    };

    /// @brief 询问是否继续执行
    /// @param IRRCode : 以引用方式返回红外线接收值
    /// @return true允许，false不允许
    virtual bool Inquire(uint16_t& IRRCode)
    {
        return true;
    };


    /// @brief 询问并等待
    /// @param ms : 等待时长，毫秒
    /// @return true允许，false不允许
    virtual bool IDelay(unsigned long ms)
    {
        delay(ms);
        return Inquire();
    };


    /// @brief 询问并等待
    /// @param ms : 等待时长，毫秒
    /// @param IRRCode : 引用方式返回获得到的红外线编码
    /// @param ReturnWhenDecode : 接收到红红外编码是否返回，默认false
    /// @return true允许，false不允许
    virtual bool IDelay(unsigned long ms, uint16_t& IRRCode, bool ReturnWhenDecode = false)
    {
        delay(ms);
        return Inquire(IRRCode);
    };
    // 返回初始位置
    // 注意这里只是将下一个菜单项设置为返回，需要功能自行退出
    virtual void GoHome()
    {
    }
};

/// @brief 功能基础类
class MMFunc {
public:
    MMFID_t FID = 0; // 功能块ID
    MMFType_t FType = 0; // 类型，共后期扩展使用
    // 所在功能池，使用方法：((MMFuncPool *)(this->FPool))->Exec(0);
    void* FPool = NULL;
    // 构造函数
    MMFunc() {};
    MMFunc(MMFID_t fid)
    {
        this->FID = fid;
    }

    /// @brief 构造函数
    /// @param fid : 当前功能块ID
    /// @param ftype : 当前功能块类型ID
    MMFunc(MMFID_t fid, MMFType_t ftype)
    {
        this->FID = fid;
        this->FType = ftype;
    }
    // virtual ~MMFunc(){};

    /// @brief 执行功能模块
    /// @note 虚函数需要子类实现
    /// @param IDelay : 传入用于询问等待的接口
    /// @return 功能块执行结果
    virtual MMFExecR_t Exec(InquireDelay* IDelay)
    {
        // if (IDelay->Inquire())
        //     delay(1000);
        // UART_USB.println("TEST");
        return EXECR_ERROR;
    };
};

#endif