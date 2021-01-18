#include "Portfolio.h"
using namespace std;
bool Portfolio::isEmpty() const
{
    return 0 == m_holdings.size();
}
void Portfolio::purchase(const string& Symbol, unsigned int ShareCount)
{
    if (0 == ShareCount) throw InvalidPurchaseException();
    m_holdings[Symbol] = ShareCount + shareCount(Symbol);
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
