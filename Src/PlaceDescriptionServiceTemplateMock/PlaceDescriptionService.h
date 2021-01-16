#pragma once

#include "Address.h"
#include "AddressExtractor.h"
#include "HttpFactory.h"

#include <memory>
#include <string>

template <typename HTTP>
class PlaceDescriptionServiceTemplate
{
public:
    // ...
    std::string summaryDescription(const std::string& Latitude, const std::string& Longitude)
    {
        auto request = createGetRequestUrl(Latitude, Longitude);
        auto response = get(request);
        return summaryDescription(response);
    }

    // mocks in tests need the reference
    HTTP& http() { return http_; }

private:
    // ...
    std::string summaryDescription(const std::string& Response) const
    {
        AddressExtractor extractor;
        auto address = extractor.addressFrom(Response);
        return address.summaryDescription();
    }

    std::string get(const std::string& Url)
    {
        http_.initialize();
        return http_.get(Url);
    }
    // ...

    std::string createGetRequestUrl(const std::string& Latitude, const std::string& Longitude) const
    {
        std::string server { "http://open.mapquestapi.com/" };
        std::string document { "nominatim/v1/reverse" };
        return server + document + "?" + keyValue("format", "json") + "&" + keyValue("lat", Latitude) + "&" +
               keyValue("lon", Longitude);
    }

    std::string keyValue(const std::string& Key, const std::string& Value) const { return Key + "=" + Value; }

    HTTP http_;
};

class HTTP;
typedef PlaceDescriptionServiceTemplate<Http> PlaceDescriptionService;
