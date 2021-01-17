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
    std::string createGetRequestUrl(const std::string& Latitude, const std::string& Longitude) const;
    std::string summaryDescription(const Address& IAddress) const;
    std::string keyValue(const std::string& Key, const std::string& Value) const;
    std::string get(const std::string& RequestUrl) const;
    std::string summaryDescription(const std::string& Response) const;
    const Http* m_http;
};