#include "Portfolio/Portfolio.h"
#include "boost/date_time/gregorian/gregorian_types.hpp"

#include "gmock/gmock.h"

using namespace ::testing;
using namespace std;
using namespace boost::gregorian;

static const boost::gregorian::date ARBITRARY_DATE(2014, boost::gregorian::Sep, 5);

class APortfolio : public Test
{
public:
    static const string IBM;
    static const string SAMSUNG;
    Portfolio m_portfolio;

    void purchase(const string& Symbol, unsigned int ShareCount, const date& TransactionDate = ARBITRARY_DATE)
    {
        m_portfolio.purchase(Symbol, ShareCount, TransactionDate);
    }

    void sell(const string& Symbol, unsigned int ShareCount, const date& TransactionDate = ARBITRARY_DATE)
    {
        m_portfolio.sell(Symbol, ShareCount, TransactionDate);
    }

    void assertPurchase(PurchaseRecord& Purchase, int ShareCount, const date& TransactionDate)
    {
        ASSERT_THAT(Purchase.m_shareCount, Eq(ShareCount));
        ASSERT_THAT(Purchase.m_date, Eq(TransactionDate));
    }
};

const string APortfolio::IBM("IBM");
const string APortfolio::SAMSUNG("SSNLF");

TEST_F(APortfolio, IsEmptyWhenCreated)
{
    ASSERT_TRUE(m_portfolio.isEmpty());
}

TEST_F(APortfolio, IsNotEmptyAfterPurchase)
{
    purchase(IBM, 1);

    ASSERT_FALSE(m_portfolio.isEmpty());
}

TEST_F(APortfolio, AnswersZeroForShareCountOfUnpurchasedSymbol)
{
    ASSERT_THAT(m_portfolio.shareCount("AAPL"), Eq(0u));
}

TEST_F(APortfolio, AnswersShareCountForPurchasedSymbol)
{
    purchase(IBM, 2);

    ASSERT_THAT(m_portfolio.shareCount(IBM), Eq(2u));
}

TEST_F(APortfolio, ThrowsOnPurchaseOfZeroShares)
{
    ASSERT_THROW(purchase(IBM, 0), ShareCountCannotBeZeroException);
}

TEST_F(APortfolio, AnswersShareCountForAppropriateSymbol)
{
    purchase(IBM, 5);
    purchase(SAMSUNG, 10);

    ASSERT_THAT(m_portfolio.shareCount(IBM), Eq(5u));
}

TEST_F(APortfolio, ShareCountReflectsAccumulatedPurchasesOfSameSymbol)
{
    purchase(IBM, 5);
    purchase(IBM, 15);

    ASSERT_THAT(m_portfolio.shareCount(IBM), Eq(5u + 15));
}

TEST_F(APortfolio, ReducesShareCountOfSymbolOnSell)
{
    purchase(SAMSUNG, 30);

    sell(SAMSUNG, 13);

    ASSERT_THAT(m_portfolio.shareCount(SAMSUNG), Eq(30u - 13));
}

TEST_F(APortfolio, ThrowsWhenSellingMoreSharesThanPurchased)
{
    ASSERT_THROW(sell(SAMSUNG, 1), InsufficientSharesException);
}

TEST_F(APortfolio, AnswersThePurchaseRecordForASinglePurchase)
{
    purchase(SAMSUNG, 5, ARBITRARY_DATE);

    auto purchases = m_portfolio.purchases(SAMSUNG);

    assertPurchase(purchases[0], 5, ARBITRARY_DATE);
}

TEST_F(APortfolio, IncludesSalesInPurchaseRecords)
{
    purchase(SAMSUNG, 10);
    sell(SAMSUNG, 5, ARBITRARY_DATE);

    auto sales = m_portfolio.purchases(SAMSUNG);

    assertPurchase(sales[1], -5, ARBITRARY_DATE);
}

TEST_F(APortfolio, ThrowsOnSellOfZeroShares)
{
    ASSERT_THROW(sell(IBM, 0), ShareCountCannotBeZeroException);
}

bool operator==(const PurchaseRecord& Lhs, const PurchaseRecord& Rhs)
{
    return Lhs.m_shareCount == Rhs.m_shareCount && Lhs.m_date == Rhs.m_date;
}

TEST_F(APortfolio, SeparatesPurchaseRecordsBySymbol)
{
    purchase(SAMSUNG, 5, ARBITRARY_DATE);
    purchase(IBM, 1, ARBITRARY_DATE);

    auto sales = m_portfolio.purchases(SAMSUNG);

    ASSERT_THAT(sales, ElementsAre(PurchaseRecord(5, ARBITRARY_DATE)));
}

TEST_F(APortfolio, AnswersEmptyPurchaseRecordVectorWhenSymbolNotFound)
{
    ASSERT_THAT(m_portfolio.purchases(SAMSUNG), Eq(vector<PurchaseRecord>()));
}

TEST_F(APortfolio, SupportsMultiplePurchaseRecordsOfSymbol)
{
    purchase(SAMSUNG, 4, ARBITRARY_DATE);
    purchase(SAMSUNG, 11, ARBITRARY_DATE);

    auto sales = m_portfolio.purchases(SAMSUNG);

    ASSERT_THAT(sales, ElementsAre(PurchaseRecord(4, ARBITRARY_DATE), PurchaseRecord(11, ARBITRARY_DATE)));
}
