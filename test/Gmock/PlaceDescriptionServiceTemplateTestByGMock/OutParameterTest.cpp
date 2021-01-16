#include "gmock/gmock.h"

using namespace ::testing;

class DifficultCollaborator
{
public:
    virtual bool calculate(int* Result) { throw 1; };
};
class Target
{
public:
    int execute(DifficultCollaborator* Calculator)
    {
        int i;
        if (!Calculator->calculate(&i)) return 0;

        return i;
    }
};

class DifficultCollaboratorMock : public DifficultCollaborator
{
public:
    MOCK_METHOD(bool, calculate, (int*), (override));
};

TEST(ATarget, ReturnsAnAmountWhenCalculatePasses)
{
    DifficultCollaboratorMock difficult;
    Target calc;
    EXPECT_CALL(difficult, calculate(_)).WillOnce(DoAll(SetArgPointee<0>(3), Return(true)));
    auto result = calc.execute(&difficult);
    ASSERT_THAT(result, Eq(3));
}