#pragma once

#include <string>

namespace stringutil
{
/**
 * @brief 获取词首字母
 *
 * @param Word
 * @return std::string
 */
std::string head(const std::string& Word);

/**
 * @brief 获取词尾子串
 *
 * @param Word
 * @return std::string
 */
std::string tail(const std::string& Word);

/**
 * @brief 对字符串进行补零
 *
 * @param Text 需要补零的字符串
 * @param ToLength 字符串需要的长度
 * @return std::string
 */
std::string zeroPad(const std::string& Text, unsigned int ToLength);

/**
 * @brief 对首字母进行大写
 *
 * @param String
 * @return std::string
 */
std::string upperFront(const std::string& String);
}   // namespace stringutil
