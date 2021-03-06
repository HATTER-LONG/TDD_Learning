#include "AddressExtractor.h"
#include "CurlHttp.h"
#include "Http.h"
#include "PlaceDescriptionService.h"

#include <memory>
#include <string>

using namespace std;
PlaceDescriptionService::PlaceDescriptionService(shared_ptr<HttpFactory> HttpFactory)
        : m_httpFactory { HttpFactory }
{
}

string PlaceDescriptionService::summaryDescription(const string& Latitude, const string& Longitude) const
{
    auto request = createGetRequestUrl(Latitude, Longitude);
    auto response = get(request);
    return summaryDescription(response);
}

string PlaceDescriptionService::summaryDescription(const string& Response) const
{
    AddressExtractor extractor;
    auto address = extractor.addressFrom(Response);
    return address.summaryDescription();
}

string PlaceDescriptionService::get(const string& Url) const
{
    auto http = m_httpFactory->get();
    http->initialize();
    return http->get(Url);
}

shared_ptr<Http> PlaceDescriptionService::httpService() const
{
    return make_shared<CurlHttp>();
}

string PlaceDescriptionService::createGetRequestUrl(const string& Latitude, const string& Longitude) const
{
    string server { "http://open.mapquestapi.com/" };
    string document { "nominatim/v1/reverse" };
    return server + document + "?" + keyValue("format", "json") + "&" + keyValue("lat", Latitude) + "&" +
           keyValue("lon", Longitude);
}

string PlaceDescriptionService::keyValue(const string& Key, const string& Value) const
{
    return Key + "=" + Value;
}
