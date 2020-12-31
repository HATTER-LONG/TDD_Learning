#include "Soundex.h"

std::string Soundex::encode(const std::string& Word) const
{
    return zeroPad(upperFront(head(Word)) + tail(encodedDigits(Word)));
}

std::string Soundex::upperFront(const std::string& String) const
{
    return std::string(1, std::toupper(static_cast<unsigned char>(String.front())));
}

char Soundex::lower(char C) const
{
    return std::tolower(static_cast<unsigned char>(C));
}

std::string Soundex::head(const std::string& Word) const
{
    return Word.substr(0, 1);
}

std::string Soundex::tail(const std::string& Word) const
{
    return Word.substr(1);
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
    if (digit != NotADigit && (isDuplicateLetter(Encoding, digit) || isVowel(LastLetter))) { Encoding += digit; }
}

bool Soundex::isVowel(char Letter) const
{
    return std::string("aeiouy").find(lower(Letter)) != std::string::npos;
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

    auto it = encodings.find(lower(Letter));
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

std::string Soundex::zeroPad(const std::string& Word) const
{
    auto zerosNeeded = MaxCodeLength - Word.length();
    return Word + std::string(zerosNeeded, '0');
}