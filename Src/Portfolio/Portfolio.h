#pragma once

#include <exception>
#include <string>

class InvalidPurchaseException : public std::exception
{
};

class Portfolio
{
public:
    Portfolio();
    bool isEmpty() const;
    void purchase(const std::string& Symbol, unsigned int ShareCount);
    unsigned int shareCount(const std::string& Symbol) const;

private:
    unsigned int m_shareCount;
};