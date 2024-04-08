/**
 * @file MMConfig.hpp
 * @date 2024/03/08 13:10:15
 * @author  
 * @version 1.0
 * @brief 设置类
 * @details 统一管理设置项，包括保存和载入
 */

#ifndef _MMCONFIG_HPP
#define _MMCONFIG_HPP

#include "MMSD.hpp"
#include <ArduinoJson.h>

/// @brief 设置类
class MMConfig {
private:
public:
    /// @brief 定义配置json
    JsonDocument Config;
    /// @brief 是否已经载入
    bool Loaded = false;
    /// @brief 是否需要保存
    bool NeedSave = false; // 是否需要保存，
    /// @brief 构造
    MMConfig()
        : Config() {};
    /// @brief 析构
    ~MMConfig() {};

    /// @brief 将设置保存
    bool Save()
    {
        bool r = false; // 定义结果
        if (mmsd.SaveJsonToFile(Config, FILENAME_CFG)) {
            NeedSave = false; // 如果保存成功则将需要保存设置为false
        }
        return r;
    }

    /// @brief 载入配置
    bool Load()
    {
        this->Loaded = mmsd.LoadJsonFromFile(Config, FILENAME_CFG);
        return this->Loaded;
    }

    /// @brief 如果需要保存则进行保存
    void SaveIfNeeded()
    {
        if (this->NeedSave)
            this->Save();
    }

} mmconfig;

#endif