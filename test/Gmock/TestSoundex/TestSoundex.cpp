#include "Soundex.h"

#include "gmock/gmock.h"
using namespace testing;

class SoundexEncoding : public Test
{
public:
    Soundex Soundex;
};

TEST_F(SoundexEncoding, RetainsSoleLetterOfOneLetterWord)
{
    ASSERT_THAT(Soundex.encode("A"), Eq("A000"));
}

TEST_F(SoundexEncoding, PadsWithZerosToEnsureThreeDigits)
{
    ASSERT_THAT(Soundex.encode("I"), Eq("I000"));
}

TEST_F(SoundexEncoding, ReplacesConsonantsWithAppropriateDigits)
{
    ASSERT_THAT(Soundex.encode("Ax"), Eq("A200"));
}

TEST_F(SoundexEncoding, IgnoresNonAlphabetics)
{
    ASSERT_THAT(Soundex.encode("A#"), Eq("A000"));
}

TEST_F(SoundexEncoding, ReplacesMultipleConsonantsWithDigits)
{
    ASSERT_THAT(Soundex.encode("Acdl"), Eq("A234"));
}

TEST_F(SoundexEncoding, LimitsLengthToFourCharacters)
{
    ASSERT_THAT(Soundex.encode("Dcdlb").length(), Eq(4u));
}

TEST_F(SoundexEncoding, IgnoresVowelLikeLetters)
{
    ASSERT_THAT(Soundex.encode("BaAeEiIoOuUhHyYcdl"), Eq("B234"));
}

TEST_F(SoundexEncoding, CombinesDuplicateEncodings)
{
    // ASSERT_THAT(Soundex.encodedDigit('b'), Eq(Soundex.encodedDigit('f')));
    // ASSERT_THAT(Soundex.encodedDigit('c'), Eq(Soundex.encodedDigit('g')));
    // ASSERT_THAT(Soundex.encodedDigit('d'), Eq(Soundex.encodedDigit('t')));

    ASSERT_THAT(Soundex.encode("Abfcgdt"), Eq("A123"));
}

TEST_F(SoundexEncoding, UppercasesFirstLetter)
{
    ASSERT_THAT(Soundex.encode("abcd"), StartsWith("A"));
}

TEST_F(SoundexEncoding, IgnoresCaseWhenEncodingConsonants)
{
    ASSERT_THAT(Soundex.encode("BCDL"), Eq(Soundex.encode("Bcdl")));
}

TEST_F(SoundexEncoding, CombinesDuplicateCodesWhen2ndLetterDuplicates1st)
{
    ASSERT_THAT(Soundex.encode("Bbcd"), Eq("B230"));
}

TEST_F(SoundexEncoding, DoesNotCombineDuplicateEncodingsSeparatedByVowels)
{
    ASSERT_THAT(Soundex.encode("Jbob"), Eq("J110"));
}
