/*
 * @File :  MMConfig.hpp
 * @Time :  2024/03/08 13:10:15
 * @Auth :
 * @Vers :  1.0
 * @Desc :  MagicMatrix设置类
 */

#ifndef _MMCONFIG_HPP
#define _MMCONFIG_HPP

#include <ArduinoJson.h>
#include "MMSD.hpp"

class MMConfig {
private:
public:
    JsonDocument Config; // 定义配置json

    // 构造
    MMConfig()
        : Config() {};
    // 析构
    ~MMConfig() {};

} mmconfig;

#endif