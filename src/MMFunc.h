/*
 * @File :  MMFunc.h
 * @Time :  2024/02/14 22:52:50
 * @Auth :  
 * @Vers :  1.0
 * @Desc :  功能块的基础类用于派生功能
 */

#ifndef MMFUNC
#define MMFUNC


// 定义处理的结果默认为两个字节
#define EXECR_OK		(0x0000)
#define EXECR_ERROR 	(0x0001) //执行错误 

// 功能基础类
class MMFunc {
public:
	uint16_t FID; // 功能块ID
	uint8_t FType = 0; // 类型，共后期扩展使用
	// 构造函数
	MMFunc(uint16_t fid) {
		this->FID = fid;
	}
	MMFunc(uint16_t fid, uint16_t ftype) {
		this->FID = fid;
        this->FType = ftype;
	}    
	// virtual ~MMFunc(){};
	virtual uint16_t Exec() {return EXECR_ERROR;}; // 虚函数需要子类实现
};


#endif