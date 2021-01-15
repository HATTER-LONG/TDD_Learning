#include "AddressExtractor.h"
#include "Http.h"
#include "PlaceDescriptionService.h"

#include <string>

using namespace std;


PlaceDescriptionService::PlaceDescriptionService(Http* IHttp)
        : MHttp(IHttp)
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
    MHttp->get(Url);
    MHttp->initialize();
    return MHttp->get(Url);
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
