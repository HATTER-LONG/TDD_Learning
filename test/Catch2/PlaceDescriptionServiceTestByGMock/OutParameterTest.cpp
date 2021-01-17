#include "catch2/catch.hpp"

#include "gmock/gmock.h"
using namespace Catch;

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

TEST_CASE("ReturnsAnAmountWhenCalculatePasses", "ATarget")
{
    DifficultCollaboratorMock difficult;
    Target calc;
    using namespace ::testing;
    EXPECT_CALL(difficult, calculate(::testing::_)).WillOnce(DoAll(SetArgPointee<0>(3), Return(true)));
    auto result = calc.execute(&difficult);
    REQUIRE(result == 3);
}