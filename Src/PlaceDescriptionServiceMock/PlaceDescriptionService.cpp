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
    string server { "http://open.mapquestapi.com/" };
    string document { "nominatim/v1/reverse" };
    // clang-format off
    string url = server + document + "?" + 
                    keyValue("format", "json") + "&" + 
                    keyValue("lat", Latitude) + "&" + 
                    keyValue("lon", Longitude);
    // clang-format on
    auto response = MHttp->get(url);
    AddressExtractor extractor;
    auto address = extractor.addressFrom(response);
    return address.summaryDescription();
}

string PlaceDescriptionService::keyValue(const std::string& Key, const std::string& Value) const
{
    return Key + "=" + Value;
}
