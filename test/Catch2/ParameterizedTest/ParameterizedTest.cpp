#include "catch2/catch.hpp"

#include <tuple>

using namespace ::Catch;


class Adder
{
public:
    static int sum(int A, int B) { return A + B; }
};

TEST_CASE("GeneratesASumFromTwoNumbers", "AnAdder")
{
    REQUIRE(Adder::sum(1, 1) == 2);
}

TEST_CASE("BulkTest", "AnAdder")
{
    using std::make_tuple;
    size_t TestInputA, TestInputB, ExpectOutPut;
    // clang-format off
    std::tie(TestInputA, TestInputB, ExpectOutPut) = 
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

    CAPTURE(TestInputA, TestInputB, ExpectOutPut);//用于记录数据信息 log
    REQUIRE(Adder::sum(TestInputA, TestInputB) == ExpectOutPut);
}
