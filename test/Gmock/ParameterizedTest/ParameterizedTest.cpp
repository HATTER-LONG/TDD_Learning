#include "gmock/gmock.h"

using namespace ::testing;

struct SumCase
{
    int m_a, m_b, m_expected;
    SumCase(int AnA, int AB, int AnExpected)
            : m_a(AnA)
            , m_b(AB)
            , m_expected(AnExpected)
    {
    }
};

class AnAdder : public TestWithParam<SumCase>
{
};

class Adder
{
public:
    static int sum(int A, int B) { return A + B; }
};

TEST(AnAdder, GeneratesASumFromTwoNumbers)
{
    ASSERT_THAT(Adder::sum(1, 1), Eq(2));
}

TEST_P(AnAdder, GeneratesLotsOfSumsFromTwoNumbers)
{
    SumCase input = GetParam();
    ASSERT_THAT(Adder::sum(input.m_a, input.m_b), Eq(input.m_expected));
}
SumCase sums[] = { SumCase(1, 1, 2), SumCase(1, 2, 3), SumCase(2, 2, 4) };
INSTANTIATE_TEST_SUITE_P(BulkTest, AnAdder, ValuesIn(sums));
