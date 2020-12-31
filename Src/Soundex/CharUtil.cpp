#include "CharUtil.h"

#include <cctype>
#include <string>

using namespace std;

namespace charutil
{
bool isVowel(char Letter)
{
    return string("aeiouy").find(tolower(Letter)) != string::npos;
}

char upper(char C)
{
    return std::toupper(static_cast<unsigned char>(C));
}

char lower(char C)
{
    return std::tolower(static_cast<unsigned char>(C));
}
}   // namespace charutil
