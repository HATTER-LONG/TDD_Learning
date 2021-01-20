#pragma once

#include <boost/date_time/gregorian/gregorian_types.hpp>
#include <exception>
#include <string>
#include <unordered_map>

class ShareCountCannotBeZeroException : public std::exception
{
};
class InsufficientSharesException : public std::exception
{
};

struct PurchaseRecord
{
    PurchaseRecord(int ShareCount, const boost::gregorian::date& Date)
            : m_shareCount(ShareCount)
            , m_date(Date)
    {
    }
    PurchaseRecord(PurchaseRecord const& Param)
            : m_shareCount(Param.m_shareCount)
            , m_date(Param.m_date)
    {
    }
    int m_shareCount;
    boost::gregorian::date m_date;
};
class Portfolio
{
public:
    bool isEmpty() const;

    void purchase(
        const std::string& Symbol, unsigned int ShareCount, const boost::gregorian::date& TransactionDate);
    void sell(
        const std::string& Symbol, unsigned int ShareCount, const boost::gregorian::date& TransactionDate);

    unsigned int shareCount(const std::string& Symbol) const;
    std::vector<PurchaseRecord> purchases(const std::string& Symbol) const;

private:
    void transact(const std::string& Symbol, int ShareChange, const boost::gregorian::date& TransactionDate);
    void updateShareCount(const std::string& Symbol, int ShareChange);
    void addPurchaseRecord(const std::string& Symbol, int ShareCount, const boost::gregorian::date& Date);
    void throwIfShareCountIsZero(int ShareChange) const;

    bool containsSymbol(const std::string& Symbol);
    void initializePurchaseRecords(const std::string& Symbol);
    void add(const std::string& Symbol, PurchaseRecord&& Record);

    template <typename T>
    T mapFind(std::unordered_map<std::string, T> Map, const std::string& Key) const
    {
        auto it = Map.find(Key);
        return it == Map.end() ? T {} : it->second;
    }

    std::unordered_map<std::string, unsigned int> m_holdings;
    std::unordered_map<std::string, std::vector<PurchaseRecord>> m_purchaseRecords;
};