#include "Soundex.h"

#include "gmock/gmock.h"
using namespace testing;

class SoundexEncoding : public Test
{
public:
    Soundex m_soundex;
};

TEST_F(SoundexEncoding, RetainsSoleLetterOfOneLetterWord)
{
    ASSERT_THAT(m_soundex.encode("A"), Eq("A000"));
}

TEST_F(SoundexEncoding, PadsWithZerosToEnsureThreeDigits)
{
    ASSERT_THAT(m_soundex.encode("I"), Eq("I000"));
}

TEST_F(SoundexEncoding, ReplacesConsonantsWithAppropriateDigits)
{
    ASSERT_THAT(m_soundex.encode("Ax"), Eq("A200"));
}

TEST_F(SoundexEncoding, IgnoresNonAlphabetics)
{
    ASSERT_THAT(m_soundex.encode("A#"), Eq("A000"));
}

TEST_F(SoundexEncoding, ReplacesMultipleConsonantsWithDigits)
{
    ASSERT_THAT(m_soundex.encode("Acdl"), Eq("A234"));
}

TEST_F(SoundexEncoding, LimitsLengthToFourCharacters)
{
    ASSERT_THAT(m_soundex.encode("Dcdlb").length(), Eq(4u));
}

TEST_F(SoundexEncoding, IgnoresVowelLikeLetters)
{
    ASSERT_THAT(m_soundex.encode("BaAeEiIoOuUhHyYcdl"), Eq("B234"));
}

TEST_F(SoundexEncoding, CombinesDuplicateEncodings)
{
    // ASSERT_THAT(Soundex.encodedDigit('b'), Eq(Soundex.encodedDigit('f')));
    // ASSERT_THAT(Soundex.encodedDigit('c'), Eq(Soundex.encodedDigit('g')));
    // ASSERT_THAT(Soundex.encodedDigit('d'), Eq(Soundex.encodedDigit('t')));

    ASSERT_THAT(m_soundex.encode("Abfcgdt"), Eq("A123"));
}

TEST_F(SoundexEncoding, UppercasesFirstLetter)
{
    ASSERT_THAT(m_soundex.encode("abcd"), StartsWith("A"));
}

TEST_F(SoundexEncoding, IgnoresCaseWhenEncodingConsonants)
{
    ASSERT_THAT(m_soundex.encode("BCDL"), Eq(m_soundex.encode("Bcdl")));
}

TEST_F(SoundexEncoding, CombinesDuplicateCodesWhen2ndLetterDuplicates1st)
{
    ASSERT_THAT(m_soundex.encode("Bbcd"), Eq("B230"));
}

TEST_F(SoundexEncoding, DoesNotCombineDuplicateEncodingsSeparatedByVowels)
{
    ASSERT_THAT(m_soundex.encode("Jbob"), Eq("J110"));
}
