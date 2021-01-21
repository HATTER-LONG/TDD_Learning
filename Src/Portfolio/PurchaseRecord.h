#pragma once
#include "boost/date_time/gregorian/gregorian_types.hpp"

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
