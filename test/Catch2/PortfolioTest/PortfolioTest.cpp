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
    static const string SAMSUNG;
    Portfolio m_portfolio;
};

const string APortfolio::IBM("IBM");
const string APortfolio::SAMSUNG("SSNLF");

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

TEST_CASE_METHOD(APortfolio, "Answers share count for appropriate symbol", "[Portfolio]")
{
    m_portfolio.purchase(IBM, 5);
    m_portfolio.purchase(SAMSUNG, 15);
    REQUIRE(m_portfolio.shareCount(IBM) == 5u);
}

TEST_CASE_METHOD(APortfolio, "share count reflects accumulated for purchases same symbol", "[Portfolio]")
{
    m_portfolio.purchase(IBM, 5);
    m_portfolio.purchase(IBM, 15);
    REQUIRE(m_portfolio.shareCount(IBM) == (5u + 15));
}

TEST_CASE_METHOD(APortfolio, "Reduces share count of symbol on sell", "[Portfolio]")
{
    m_portfolio.purchase(SAMSUNG, 30);
    m_portfolio.sell(SAMSUNG, 13);

    REQUIRE(m_portfolio.shareCount(SAMSUNG) == (30u - 13));
}

TEST_CASE_METHOD(APortfolio, "Throw when selling more shares than purchased", "[Portfolio]")
{
    REQUIRE_THROWS_AS(m_portfolio.sell(SAMSUNG, 1), InvalidSellException);
}

TEST_CASE_METHOD(APortfolio, "Answers the purchase record for a single purchase")
{
    using boost::gregorian::date;
    m_portfolio.purchase(SAMSUNG, 5);
    auto purchases = m_portfolio.purchases(SAMSUNG);

    auto purchase = purchases[0];
    REQUIRE(purchase.m_shareCount == 5u);
    REQUIRE(purchase.m_date == Portfolio::FIXED_PURCHASE_DATE);
}