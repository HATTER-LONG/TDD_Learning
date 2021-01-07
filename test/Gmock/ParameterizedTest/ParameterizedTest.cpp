#include "gmock/gmock.h"

using namespace ::testing;

struct SumCase
{
    int A, B, Expected;
    SumCase(int AnA, int AB, int AnExpected)
            : A(AnA)
            , B(AB)
            , Expected(AnExpected)
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
    ASSERT_THAT(Adder::sum(input.A, input.B), Eq(input.Expected));
}
SumCase sums[] = { SumCase(1, 1, 2), SumCase(1, 2, 3), SumCase(2, 2, 4) };
INSTANTIATE_TEST_SUITE_P(BulkTest, AnAdder, ValuesIn(sums));
