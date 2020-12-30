#pragma once

#include <cstddef>
#include <string>
#include <unordered_map>

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
    std::string encode(const std::string& Word) const { return zeroPad(head(Word) + encodedDigits(tail(Word))); }

private:
    /**
     * @brief 获取单词的第一个字母
     *
     * @param Word
     * @return std::string
     */
    std::string head(const std::string& Word) const { return Word.substr(0, 1); }

    /**
     * @brief 获取单词除了第一个字母外的其余字母
     *
     * @param Word
     * @return std::string
     */
    std::string tail(const std::string& Word) const { return Word.substr(1); }

    /**
     * @brief 获取首字母后其他字符转化的对应数字
     *
     * @param Word
     * @return std::string
     */
    std::string encodedDigits(const std::string& Word) const
    {
        std::string encoding;
        for (auto letter : Word)
            encoding += encodedDigit(letter);
        return encoding;
    }

    /**
     * @brief 获取一个字符对应的数字
     *
     * @param Letter
     * @return std::string
     */
    std::string encodedDigit(char Letter) const
    {
        // clang-format off
        const std::unordered_map<char, std::string> encodings { 
            { 'b', "1" }, { 'f', "1" }, { 'p', "1" }, { 'v', "1" },
            { 'c', "2" }, { 'g', "2" }, { 'j', "2" }, { 'k', "2" }, { 'q', "2" }, 
                                        { 's', "2" }, { 'x', "2" }, { 'z', "2" },
            { 'd', "3" }, { 't', "3" }, 
            { 'l', "4" }, 
            { 'm', "5" }, { 'n', "5" }, 
            { 'r', "6" } };
        // clang-format on

        auto it = encodings.find(Letter);
        return it == encodings.end() ? "" : it->second;
    }
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
