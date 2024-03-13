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
    bool NeedSave = false; // 是否需要保存，
    // 构造
    MMConfig()
        : Config() {};
    // 析构
    ~MMConfig() {};

    // 将文档保存
    bool Save()
    {
        bool r = false; // 定义结果
        if (mmsd.SaveJsonToFile(Config, CFG_FILENAME)) {
            NeedSave = false; // 如果保存成功则将需要保存设置为false
        }
        return r;
    }
    
    // 读取
    bool Load()
    {
        this->Loaded = mmsd.LoadJsonFromFile(Config, CFG_FILENAME);
        return this->Loaded;
    }    

    // 如果需要保存则进行保存
    void SaveIfNeeded() {
        if (this->NeedSave) this->Save();
    }

} mmconfig;

#endif