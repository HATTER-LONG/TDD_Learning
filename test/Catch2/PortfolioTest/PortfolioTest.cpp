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
    void sell(const string& Symbol, unsigned int ShareCount,
        const date& TransactionDate = APortfolio::ARBITRARY_DATE)
    {
        m_portfolio.sell(Symbol, ShareCount, TransactionDate);
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
    REQUIRE_THROWS_AS(purchase(IBM, 0), ShareCountCannotBeZeroException);
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
    sell(SAMSUNG, 13);

    REQUIRE(m_portfolio.shareCount(SAMSUNG) == (30u - 13));
}

TEST_CASE_METHOD(APortfolio, "Throw when selling more shares than purchased", "[Portfolio]")
{
    REQUIRE_THROWS_AS(sell(SAMSUNG, 1), InsufficientSharesException);
}

TEST_CASE_METHOD(APortfolio, "Answers the purchase record for a single purchase", "[Portfolio]")
{
    purchase(SAMSUNG, 5, ARBITRARY_DATE);

    auto purchases = m_portfolio.purchases(SAMSUNG);
    REQUIRE(purchases[0].m_shareCount == 5u);
    REQUIRE(purchases[0].m_date == ARBITRARY_DATE);
}

TEST_CASE_METHOD(APortfolio, "Includes sales in purchase records", "[Portfolio]")
{
    purchase(SAMSUNG, 10);
    m_portfolio.sell(SAMSUNG, 5, ARBITRARY_DATE);

    auto sales = m_portfolio.purchases(SAMSUNG);
    REQUIRE(sales[1].m_shareCount == -5u);
    REQUIRE(sales[1].m_date == ARBITRARY_DATE);
}

TEST_CASE_METHOD(APortfolio, "Throws on sell of zero shares", "[Portfolio]")
{
    REQUIRE_THROWS_AS(sell(IBM, 0), ShareCountCannotBeZeroException);
}

bool operator==(const PurchaseRecord& Lhs, const PurchaseRecord& Rhs)
{
    return Lhs.m_shareCount == Rhs.m_shareCount && Lhs.m_date == Rhs.m_date;
}

// TODO: 使用新式方法实现一个 Matcher 匹配器
// https://github.com/catchorg/Catch2/blob/devel/docs/matchers.md
class ElementsAre : public Catch::MatcherBase<vector<PurchaseRecord>>
{
public:
    ElementsAre(const vector<PurchaseRecord>& Param)
            : m_purchaseRecord(Param)
    {
    }
    bool match(vector<PurchaseRecord> const& Arg) const override
    {
        for (auto varL : Arg)
        {
            if (!checkMemberInVec(varL)) return false;
        }
        return true;
    }
    bool checkMemberInVec(const PurchaseRecord& Member) const
    {
        bool retFlag = false;
        for (auto varR : m_purchaseRecord)
            if (Member == varR) { retFlag = true; }
        return retFlag;
    }
    virtual std::string describe() const override { return "None Match"; }


private:
    vector<PurchaseRecord> m_purchaseRecord;
};

TEST_CASE_METHOD(APortfolio, "Separates purchase records by symbol", "[Portfolio]")
{
    purchase(SAMSUNG, 5, ARBITRARY_DATE);
    purchase(IBM, 1, ARBITRARY_DATE);

    auto sales = m_portfolio.purchases(SAMSUNG);
    vector<PurchaseRecord> checkArray { PurchaseRecord(5, ARBITRARY_DATE) };
    REQUIRE_THAT(sales, ElementsAre(checkArray));
}

bool operator!=(const PurchaseRecord& Lhs, const PurchaseRecord& Rhs)
{
    return !(Lhs == Rhs);
}
TEST_CASE_METHOD(APortfolio, "Answers empty purchase record vector when symbol not found", "[Portfolio]")
{
    REQUIRE_THAT(m_portfolio.purchases(SAMSUNG), Equals(vector<PurchaseRecord>()));
}