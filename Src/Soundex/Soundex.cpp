#include "CharUtil.h"
#include "Soundex.h"
#include "StringUtil.h"

std::string Soundex::encode(const std::string& Word) const
{
    return stringutil::zeroPad(
        stringutil::upperFront(stringutil::head(Word)) + stringutil::tail(encodedDigits(Word)), MaxCodeLength);
}

bool Soundex::isComplete(const std::string& Encoding) const
{
    return Encoding.length() == MaxCodeLength;
}

std::string Soundex::encodedDigits(const std::string& Word) const
{
    std::string encoding;
    encodeHead(encoding, Word);
    encodeTail(encoding, Word);
    return encoding;
}

void Soundex::encodeHead(std::string& Encoding, const std::string& Word) const
{
    Encoding += encodedDigit(Word.front());
}

void Soundex::encodeTail(std::string& Encoding, const std::string& Word) const
{
    for (auto i = 1u; i < Word.length(); i++)
    {
        if (!isComplete(Encoding)) { encodeLetter(Encoding, Word[i], Word[i - 1]); }
    }
}

void Soundex::encodeLetter(std::string& Encoding, char Letter, char LastLetter) const
{
    auto digit = encodedDigit(Letter);
    if (digit != NotADigit && (isDuplicateLetter(Encoding, digit) || charutil::isVowel(LastLetter))) { Encoding += digit; }
}

std::string Soundex::encodedDigit(char Letter) const
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

    auto it = encodings.find(charutil::lower(Letter));
    return it == encodings.end() ? NotADigit : it->second;
}

bool Soundex::isDuplicateLetter(std::string& Encoding, std::string& Letter) const
{
    return Letter != lastDigit(Encoding);
}

std::string Soundex::lastDigit(const std::string& Encoding) const
{
    if (Encoding.empty()) return NotADigit;
    return std::string(1, Encoding.back());   // string 初始化一个字符的方法
}
