#pragma once

#include <string>

class Http;

class PlaceDescriptionService
{
public:
    PlaceDescriptionService(Http* IHttp);
    std::string summaryDescription(const std::string& Latitude, const std::string& Longitude) const;

private:
    Http* MHttp;
};