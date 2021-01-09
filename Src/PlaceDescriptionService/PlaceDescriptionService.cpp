#include "PlaceDescriptionService.h"

#include <string>

using namespace std;


PlaceDescriptionService::PlaceDescriptionService(Http* IHttp)
        : MHttp(IHttp)
{
}

string PlaceDescriptionService::summaryDescription(const string& Latitude, const string& Longitude) const
{
    return "";
}