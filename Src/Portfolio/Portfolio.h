#pragma once

#include <exception>
#include <string>
#include <unordered_map>

class InvalidPurchaseException : public std::exception
{
};
class InvalidSellException : public std::exception
{
};
class Portfolio
{
public:
    bool isEmpty() const;
    void purchase(const std::string& Symbol, unsigned int ShareCount);
    void sell(const std::string& Symbol, unsigned int ShareCount);
    unsigned int shareCount(const std::string& Symbol) const;

private:
    std::unordered_map<std::string, unsigned int> m_holdings;
};