#include "catch2/catch.hpp"

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
    std::string encode(const std::string& Word) const { return ""; }
};

TEST_CASE("Retain sole letter of one letter world", "[SoundexEncoding]")
{
    GIVEN("A soundex var")
    {
        Soundex soundex;

        WHEN("Input one char")
        {
            auto encoded = soundex.encode("A");
            THEN("Check that the return value is correct") { REQUIRE_THAT(encoded, Equals("A")); }
        }
    }
}