#include "Portfolio.h"
using namespace std;
using namespace boost::gregorian;

bool Portfolio::isEmpty() const
{
    return 0 == m_holdings.size();
}
void Portfolio::purchase(const string& Symbol, unsigned int ShareCount, const date& TransactionDate)
{
    transact(Symbol, ShareCount, TransactionDate);
}
void Portfolio::sell(const std::string& Symbol, unsigned int ShareCount, const date& TransactionDate)
{
    if (ShareCount > shareCount(Symbol)) throw InsufficientSharesException();
    transact(Symbol, -ShareCount, TransactionDate);
}

void Portfolio::transact(
    const std::string& Symbol, int ShareChange, const boost::gregorian::date& TransactionDate)
{
    if (0 == ShareChange) throw ShareCountCannotBeZeroException();
    m_holdings[Symbol] = shareCount(Symbol) + ShareChange;
    m_purchases.push_back(PurchaseRecord(ShareChange, TransactionDate));
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