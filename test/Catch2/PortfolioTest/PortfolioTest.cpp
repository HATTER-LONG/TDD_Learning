#include "Portfolio/Portfolio.h"
#include "catch2/catch.hpp"

#include <boost/date_time/gregorian/greg_month.hpp>
#include <unistd.h>
using namespace Catch;
using namespace std;
using boost::gregorian::date;
TEST_CASE("Create portfolio example")
{
    Portfolio portfolio;
}

class APortfolio
{
public:
    static const date ARBITRARY_DATE;

    static const string IBM;
    static const string SAMSUNG;
    void purchase(const string& Symbol, unsigned int ShareCount,
        const date& TransactionDate = APortfolio::ARBITRARY_DATE)
    {
        m_portfolio.purchase(Symbol, ShareCount, ARBITRARY_DATE);
    }
    Portfolio m_portfolio;
};
const date APortfolio::ARBITRARY_DATE(2021, boost::gregorian::Jul, 19);
const string APortfolio::IBM("IBM");
const string APortfolio::SAMSUNG("SSNLF");

TEST_CASE_METHOD(APortfolio, "Is empty whe created", "[Portfolio]")
{
    REQUIRE(m_portfolio.isEmpty());
}

TEST_CASE_METHOD(APortfolio, "Is not empty after purchase", "[Portfolio]")
{
    purchase(IBM, 1);
    REQUIRE_FALSE(m_portfolio.isEmpty());
}

TEST_CASE_METHOD(APortfolio, "Answers zero for share count of no purchased symbol", "[Portfolio]")
{
    REQUIRE(m_portfolio.shareCount("AAPL") == 0u);
}

TEST_CASE_METHOD(APortfolio, "Answers share count for purchased symbol", "[Portfolio]")
{
    m_portfolio.purchase(IBM, 2, ARBITRARY_DATE);
    REQUIRE(m_portfolio.shareCount(IBM) == 2u);
}

TEST_CASE_METHOD(APortfolio, "Throw on purchase of zero shares", "[Portfolio]")
{
    REQUIRE_THROWS_AS(purchase(IBM, 0), InvalidPurchaseException);
}

TEST_CASE_METHOD(APortfolio, "Answers share count for appropriate symbol", "[Portfolio]")
{
    purchase(IBM, 5);
    purchase(SAMSUNG, 15);
    REQUIRE(m_portfolio.shareCount(IBM) == 5u);
}

TEST_CASE_METHOD(APortfolio, "share count reflects accumulated for purchases same symbol", "[Portfolio]")
{
    purchase(IBM, 5);
    purchase(IBM, 15);
    REQUIRE(m_portfolio.shareCount(IBM) == (5u + 15));
}

TEST_CASE_METHOD(APortfolio, "Reduces share count of symbol on sell", "[Portfolio]")
{
    purchase(SAMSUNG, 30);
    m_portfolio.sell(SAMSUNG, 13);

    REQUIRE(m_portfolio.shareCount(SAMSUNG) == (30u - 13));
}

TEST_CASE_METHOD(APortfolio, "Throw when selling more shares than purchased", "[Portfolio]")
{
    REQUIRE_THROWS_AS(m_portfolio.sell(SAMSUNG, 1), InvalidSellException);
}

TEST_CASE_METHOD(APortfolio, "Answers the purchase record for a single purchase")
{

    date dateOfPurchase(2021, boost::date_time::Mar, 17);

    m_portfolio.purchase(SAMSUNG, 5, dateOfPurchase);
    auto purchases = m_portfolio.purchases(SAMSUNG);

    auto purchase = purchases[0];
    REQUIRE(purchase.m_shareCount == 5u);
    REQUIRE(purchase.m_date == dateOfPurchase);
}