#pragma once
#include <string>

struct Address
{
    std::string Road;
    std::string City;
    std::string State;
    std::string Country;
    std::string summaryDescription() const { return Road + ", " + City + ", " + State + ", " + Country; }
};
