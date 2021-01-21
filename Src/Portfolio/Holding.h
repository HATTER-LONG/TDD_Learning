#pragma once
#include "PurchaseRecord.h"

#include <numeric>
class Holding
{
public:
    void add(PurchaseRecord& Record) { m_purchaseRecords.push_back(Record); }

    std::vector<PurchaseRecord> purchases() const { return m_purchaseRecords; }

    unsigned int shareCount() const
    {
        return accumulate(m_purchaseRecords.begin(), m_purchaseRecords.end(), 0,
            [](int Total, PurchaseRecord Record) { return Total + Record.m_shareCount; });
    }

private:
    std::vector<PurchaseRecord> m_purchaseRecords;
};
