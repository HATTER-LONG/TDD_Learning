#pragma once
#include "Location.h"

class User
{
public:
    User(const std::string& name, Location location)
            : name_(name)
            , location_(location)
    {
    }
    std::string name() { return name_; }
    Location location() { return location_; }

private:
    std::string name_;
    Location location_;
};
