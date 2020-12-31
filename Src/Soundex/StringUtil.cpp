#include "CharUtil.h"
#include "StringUtil.h"

namespace stringutil
{
std::string head(const std::string& Word)
{
    return Word.substr(0, 1);
}

std::string tail(const std::string& Word)
{
    if (Word.length() == 0) return "";
    return Word.substr(1);
}

std::string zeroPad(const std::string& Text, unsigned int ToLength)
{
    auto zerosNeeded = ToLength - Text.length();
    return Text + std::string(zerosNeeded, '0');
}

std::string upperFront(const std::string& String)
{
    return std::string(1, charutil::upper(String.front()));
}
}   // namespace stringutil
