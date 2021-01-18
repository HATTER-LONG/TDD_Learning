#include "Portfolio.h"
using namespace std;
Portfolio::Portfolio()
        : m_shareCount { 0u }
{
}
bool Portfolio::isEmpty() const
{
    return 0 == m_shareCount;
}

void Portfolio::purchase(const string& Symbol, unsigned int ShareCount)
{
    if (0 == ShareCount) throw InvalidPurchaseException();
    m_shareCount = ShareCount;
}

unsigned int Portfolio::shareCount(const string& Symbol) const
{
    return m_shareCount;
}
