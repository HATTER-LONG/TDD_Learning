#include "catch2/catch.hpp"

#include <tuple>

using namespace ::Catch;

class Adder
{
public:
    static size_t sum(int A, int B) { return A + B; }
};

TEST_CASE("GeneratesASumFromTwoNumbers", "AnAdder")
{
    REQUIRE(Adder::sum(1, 1) == 2);
}

TEST_CASE("BulkTest", "AnAdder")
{
    using std::make_tuple;
    size_t testInputA, testInputB, expectOutPut;
    // clang-format off
    std::tie(testInputA, testInputB, expectOutPut) = 
        GENERATE(table<size_t, size_t, size_t>(
                { 
                    make_tuple(1, 2, 3), 
                    make_tuple(2, 3, 5),  
                    make_tuple(3, 3, 6),
                    make_tuple(4, 4, 8),  
                } 
            )
        );
    //clang-format on

    CAPTURE(testInputA, testInputB, expectOutPut);//用于记录数据信息 log
    REQUIRE(Adder::sum(testInputA, testInputB) == expectOutPut);
}
