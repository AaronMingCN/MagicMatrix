/*
 * @File :  MMConfig.hpp
 * @Time :  2024/03/08 13:10:15
 * @Auth :
 * @Vers :  1.0
 * @Desc :  MagicMatrix设置类
 */

#ifndef _MMCONFIG_HPP
#define _MMCONFIG_HPP

#include "MMSD.hpp"
#include <ArduinoJson.h>

class MMConfig {
private:
public:
    JsonDocument Config; // 定义配置json
    bool Loaded = false; // 是否已经载入
    // 构造
    MMConfig()
        : Config() {};
    // 析构
    ~MMConfig() {};

    // 将文档保存
    bool Save()
    {
        return mmsd.SaveJsonToFile(Config, CFG_FILENAME);
    }
    
    // 读取
    bool Load()
    {
        this->Loaded = mmsd.LoadJsonFromFile(Config, CFG_FILENAME);
        return this->Loaded;
    }    

} mmconfig;

#endif