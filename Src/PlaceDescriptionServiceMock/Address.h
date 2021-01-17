#pragma once
#include <string>

struct Address
{
    std::string m_road;
    std::string m_city;
    std::string m_state;
    std::string m_country;
    std::string summaryDescription() const
    {
        return m_road + ", " + m_city + ", " + m_state + ", " + m_country;
    }
};
