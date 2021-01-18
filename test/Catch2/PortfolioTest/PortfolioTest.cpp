#include "Portfolio/Portfolio.h"
#include "catch2/catch.hpp"
using namespace Catch;
using namespace std;

TEST_CASE("Create portfolio example")
{
    Portfolio portfolio;
}

class APortfolio
{
public:
    static const string IBM;
    Portfolio m_portfolio;
};

const string APortfolio::IBM("IBM");

TEST_CASE_METHOD(APortfolio, "Is empty whe created", "[Portfolio]")
{
    REQUIRE(m_portfolio.isEmpty());
}

TEST_CASE_METHOD(APortfolio, "Is not empty after purchase", "[Portfolio]")
{
    m_portfolio.purchase(IBM, 1);
    REQUIRE_FALSE(m_portfolio.isEmpty());
}

TEST_CASE_METHOD(APortfolio, "Answers zero for share count of no purchased symbol", "[Portfolio]")
{
    REQUIRE(m_portfolio.shareCount("AAPL") == 0u);
}

TEST_CASE_METHOD(APortfolio, "Answers share count for purchased symbol", "[Portfolio]")
{
    m_portfolio.purchase(IBM, 2);
    REQUIRE(m_portfolio.shareCount(IBM) == 2u);
}

TEST_CASE_METHOD(APortfolio, "Throw on purchase of zero shares", "[Portfolio]")
{
    REQUIRE_THROWS_AS(m_portfolio.purchase(IBM, 0), InvalidPurchaseException);
}