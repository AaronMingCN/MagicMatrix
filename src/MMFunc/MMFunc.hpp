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
#define EXECR_OK (0x0000)
#define EXECR_ERROR (0x0001) // 执行错误

// 定义功能ID类型
typedef uint16_t MMFID_t;

// 定义功能type类型
typedef uint8_t MMFType_t;

// 定义功能执行结果类型
typedef uint16_t MMFExecR_t;

// 功能基础类
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
    MMFunc(MMFID_t fid, MMFType_t ftype)
    {
        this->FID = fid;
        this->FType = ftype;
    }
    // virtual ~MMFunc(){};
    virtual MMFExecR_t Exec() { return EXECR_ERROR; }; // 虚函数需要子类实现
};

#endif