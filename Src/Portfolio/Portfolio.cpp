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
    if (ShareCount > shareCount(Symbol))
        throw InsufficientSharesException();
    transact(Symbol, -ShareCount, TransactionDate);
}

void Portfolio::transact(
    const std::string& Symbol, int ShareChange, const boost::gregorian::date& TransactionDate)
{
    throwIfShareCountIsZero(ShareChange);
    updateShareCount(Symbol, ShareChange);
    addPurchaseRecord(Symbol, ShareChange, TransactionDate);
}

void Portfolio::throwIfShareCountIsZero(int ShareChange) const
{
    if (0 == ShareChange)
        throw ShareCountCannotBeZeroException();
}

void Portfolio::updateShareCount(const string& Symbol, int ShareChange)
{
    m_holdings[Symbol] = shareCount(Symbol) + ShareChange;
}

void Portfolio::addPurchaseRecord(const std::string& Symbol, int ShareChange, const date& Date)
{
    if (!containsSymbol(Symbol))
    {
        initializePurchaseRecords(Symbol);
    }
    add(Symbol, { ShareChange, Date });
}

void Portfolio::initializePurchaseRecords(const string& Symbol)
{
    m_purchaseRecords[Symbol] = vector<PurchaseRecord>();
}
void Portfolio::add(const string& Symbol, PurchaseRecord&& Record)
{
    m_purchaseRecords[Symbol].push_back(Record);
}

bool Portfolio::containsSymbol(const string& Symbol)
{
    return m_purchaseRecords.find(Symbol) != m_purchaseRecords.end();
}

unsigned int Portfolio::shareCount(const string& Symbol) const
{
    return mapFind<unsigned int>(m_holdings, Symbol);
}

vector<PurchaseRecord> Portfolio::purchases(const std::string& Symbol) const
{
    return mapFind<vector<PurchaseRecord>>(m_purchaseRecords, Symbol);
}