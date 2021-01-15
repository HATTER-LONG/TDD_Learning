#pragma once

#include "Address.h"

#include <string>

class Http;

class PlaceDescriptionService
{
public:
    PlaceDescriptionService(Http* IHttp);
    std::string summaryDescription(const std::string& Latitude, const std::string& Longitude) const;

private:
    std::string keyValue(const std::string& Key, const std::string& Value) const;
    const Http* MHttp;
};