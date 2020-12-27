#include "catch2/catch.hpp"
#include "spdlog/spdlog.h"
using namespace Catch;

// TODO : 当前暂时与测试代码同一个文件，当感觉代码放在同一个文件有些麻烦时，再用合适的方式迁出
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
    std::string encode(const std::string& Word) const { return zeroPad(Word); }

private:
    /**
     * @brief 安装 Soundex 条款4 要求进行补零
     *
     * @param Word
     * @return std::string
     */
    std::string zeroPad(const std::string& Word) const { return Word + "000"; }
};

class FixtureSoundex
{
public:
    Soundex MSoundex;
};

TEST_CASE_METHOD(FixtureSoundex, "Retain sole letter of one letter world", "[SoundexEncoding]")
{
    GIVEN("A MSoundex member")
    {
        WHEN("Input one char")
        {
            auto encoded = MSoundex.encode("A");
            THEN("Check that the return value is correct") { REQUIRE_THAT(encoded, Equals("A000")); }
        }
    }
}

TEST_CASE_METHOD(FixtureSoundex, "Pads with zeros to ensure three digits", "[SoundexEncoding]")
{
    GIVEN("A MSoundex member")
    {
        WHEN("Input one char")
        {
            auto encoded = MSoundex.encode("I");
            THEN("Check that the return value pads with zeros") { REQUIRE_THAT(encoded, Equals("I000")); }
        }
    }
}