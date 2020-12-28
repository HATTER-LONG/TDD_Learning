#pragma once

#include <cstddef>
#include <string>

// TODO: 暂时将实现也都放入同一个文件中比较方便修改，后续合适的时机抽出

static const size_t MaxCodeLength { 4 };
/**
 * @brief Soundex 算法类
 *
 */
class Soundex
{
public:
    /**
     * @brief 按照 Soundex 算法转换输入的字符串内容
     *
     * @param word
     * @return std::string
     */
    std::string encode(const std::string& Word) const { return zeroPad(head(Word) + encodedDigits(Word)); }

private:
    /**
     * @brief 获取单词的第一个字母
     *
     * @param Word
     * @return std::string
     */
    std::string head(const std::string& Word) const { return Word.substr(0, 1); }

    /**
     * @brief 获取首字母后其他字符转化的对应数字
     *
     * @param Word
     * @return std::string
     */
    std::string encodedDigits(const std::string& Word) const
    {
        if (Word.length() > 1) return encodedDigit();
        return "";
    }

    /**
     * @brief 获取一个字符对应的数字
     *
     * @return std::string
     */
    std::string encodedDigit() const { return "1"; }
    /**
     * @brief 安装 Soundex 的规则要求进行补零
     *
     * @param Word
     * @return std::string
     */
    std::string zeroPad(const std::string& Word) const
    {
        auto zerosNeeded = MaxCodeLength - Word.length();
        return Word + std::string(zerosNeeded, '0');
    }
};
