#pragma once

namespace charutil
{
/**
 * @brief 判断输入的 letter 是否为元音字母
 *
 * @param Letter
 * @return true
 * @return false
 */
bool isVowel(char Letter);

/**
 * @brief 将输入的字符转换为大写
 *
 * @param C
 * @return char
 */
char upper(char C);

/**
 * @brief 将输入的字符转换为小写
 *
 * @param C
 * @return char
 */
char lower(char C);
}   // namespace charutil