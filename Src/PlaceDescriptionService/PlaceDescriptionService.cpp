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
    const auto* getRequestUrl = "";
    auto jsonResponse = MHttp->get(getRequestUrl);
    AddressExtractor extractor;
    auto address = extractor.addressFrom(jsonResponse);
    return address.Road + ", " + address.City + ", " + address.State + ", " + address.Country;
}