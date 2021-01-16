#pragma once

#include "Address.h"

#include <json/reader.h>
#include <json/value.h>
#include <string>

class AddressExtractor
{
public:
    Address addressFrom(const std::string& Json) const;

private:
    Json::Value jsonAddressFrom(const std::string& Json) const;
    void populate(Address& Address, Json::Value& JsonAddress) const;
    Json::Value parse(const std::string& Json) const;
    std::string getString(Json::Value& Result, const std::string& Name) const;
};
