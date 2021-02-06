#include "AddressExtractor.h"

#include <string>

using namespace std;
using namespace Json;

Address AddressExtractor::addressFrom(const string& Json) const
{
    Address address;
    Value jsonAddress { jsonAddressFrom(Json) };
    populate(address, jsonAddress);
    return address;
}

Value AddressExtractor::jsonAddressFrom(const string& Json) const
{
    auto location = parse(Json);
    return location.get("address", Value::null);
}

void AddressExtractor::populate(Address& Address, Value& JsonAddress) const
{
    Address.m_road = getString(JsonAddress, "road");
    Address.m_city = getString(JsonAddress, "city");
    Address.m_state = getString(JsonAddress, "state");
    Address.m_country = getString(JsonAddress, "country");
}

Value AddressExtractor::parse(const string& Json) const
{
    Value root;
    CharReaderBuilder b;
    CharReader* reader(b.newCharReader());
    JSONCPP_STRING errs;
    reader->parse(Json.c_str(), Json.c_str() + Json.length(), &root, &errs);
    return root;
}

string AddressExtractor::getString(Value& Result, const string& Name) const
{
    return Result.get(Name, "").asString();
}
