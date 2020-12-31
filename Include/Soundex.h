#pragma once

#include <cctype>
#include <cstddef>
#include <string>
#include <unordered_map>

static const size_t MaxCodeLength { 4 };
const std::string NotADigit("*");

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
    std::string encode(const std::string& Word) const;

private:
    /**
     * @brief 返回传入的字符串首字母大写
     *
     * @param String
     * @return std::string
     */
    std::string upperFront(const std::string& String) const;

    /**
     * @brief 将输入的 char 字符转换为小写
     *
     * @param C
     * @return char
     */
    char lower(char C) const;

    /**
     * @brief 获取单词的第一个字母
     *
     * @param Word
     * @return std::string
     */
    std::string head(const std::string& Word) const;

    /**
     * @brief 获取单词除了第一个字母外的其余字母
     *
     * @param Word
     * @return std::string
     */
    std::string tail(const std::string& Word) const;

    /**
     * @brief 完成字符串的 Soundex 规则编码
     *
     * @param Encoding
     * @return true
     * @return false
     */
    bool isComplete(const std::string& Encoding) const;

    /**
     * @brief 获取首字母后其他字符转化的对应数字
     *
     * @param Word
     * @return std::string
     */
    std::string encodedDigits(const std::string& Word) const;

    /**
     * @brief 对词首字母进行编码翻译
     *
     * @param Encoding
     * @param Word
     */
    void encodeHead(std::string& Encoding, const std::string& Word) const;

    /**
     * @brief 对词尾字符进行编码翻译
     *
     * @param Encoding
     * @param Word
     */
    void encodeTail(std::string& Encoding, const std::string& Word) const;

    /**
     * @brief 翻译单一字符 letter 并拼接到 Encoding
     *
     * @param Encoding
     * @param Letter
     */
    void encodeLetter(std::string& Encoding, char Letter, char LastLetter) const;

    /**
     * @brief 判断是否是元音字符
     *
     * @param Letter
     * @return true
     * @return false
     */
    bool isVowel(char Letter) const;

    /**
     * @brief 获取一个字符对应的数字
     *
     * @param Letter
     * @return std::string
     */
    std::string encodedDigit(char Letter) const;

    /**
     * @brief 判断是否重复的字符
     *
     * @param Encoding
     * @param Letter
     * @return true
     * @return false
     */
    bool isDuplicateLetter(std::string& Encoding, std::string& Letter) const;

    /**
     * @brief 获取 Encoding 最后一个字符
     *
     * @param Encoding
     * @return std::string
     */
    std::string lastDigit(const std::string& Encoding) const;

    /**
     * @brief 安装 Soundex 的规则要求进行补零
     *
     * @param Word
     * @return std::string
     */
    std::string zeroPad(const std::string& Word) const;
};
