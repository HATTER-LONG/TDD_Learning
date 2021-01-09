#pragma once

#include <string>

/**
 * @brief Http 协议接口
 *
 */
class Http
{
public:
    virtual ~Http() { }

    /**
     * @brief 初始化
     *
     */
    virtual void initialize() = 0;

    /**
     * @brief 获取 URL 访问返回的信息
     *
     * @param 需要访问的 Url
     * @return std::string
     */
    virtual std::string get(const std::string& Url) const = 0;
};