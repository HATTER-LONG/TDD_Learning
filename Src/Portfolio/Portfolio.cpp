#include "Portfolio.h"
using namespace std;
using namespace boost::gregorian;

const date Portfolio::FIXED_PURCHASE_DATE(date(2021, Jan, 18));
bool Portfolio::isEmpty() const
{
    return 0 == m_holdings.size();
}
void Portfolio::purchase(const string& Symbol, unsigned int ShareCount)
{
    if (0 == ShareCount) throw InvalidPurchaseException();
    m_holdings[Symbol] = ShareCount + shareCount(Symbol);
    m_purchases.push_back(PurchaseRecord(ShareCount, FIXED_PURCHASE_DATE));
}
void Portfolio::sell(const std::string& Symbol, unsigned int ShareCount)
{
    if (ShareCount > shareCount(Symbol)) throw InvalidSellException();
    m_holdings[Symbol] = shareCount(Symbol) - ShareCount;
}

unsigned int Portfolio::shareCount(const string& Symbol) const
{
    auto it = m_holdings.find(Symbol);
    if (it == m_holdings.end()) return 0;
    return it->second;
}

vector<PurchaseRecord> Portfolio::purchases(const std::string& Symbol) const
{
    return m_purchases;
}