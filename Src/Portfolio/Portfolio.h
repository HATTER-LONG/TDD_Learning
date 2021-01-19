#pragma once

#include "boost/date_time/gregorian/gregorian_types.hpp"

#include <boost/date_time/gregorian/greg_date.hpp>
#include <exception>
#include <string>
#include <unordered_map>
class InvalidPurchaseException : public std::exception
{
};
class InvalidSellException : public std::exception
{
};

struct PurchaseRecord
{
    PurchaseRecord(unsigned int ShareCount, const boost::gregorian::date& Date)
            : m_shareCount(ShareCount)
            , m_date(Date)
    {
    }

    unsigned int m_shareCount;
    boost::gregorian::date m_date;
};
class Portfolio
{
public:
    bool isEmpty() const;

    void purchase(
        const std::string& Symbol, unsigned int ShareCount, const boost::gregorian::date& TransactionDate);
    void sell(const std::string& Symbol, unsigned int ShareCount);

    unsigned int shareCount(const std::string& Symbol) const;
    std::vector<PurchaseRecord> purchases(const std::string& Symbol) const;

private:
    std::unordered_map<std::string, unsigned int> m_holdings;
    std::vector<PurchaseRecord> m_purchases;
};