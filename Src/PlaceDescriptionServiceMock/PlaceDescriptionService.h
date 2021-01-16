#pragma once

#include "Address.h"

#include <memory>
#include <string>

class Http;

class PlaceDescriptionService
{
public:
    virtual ~PlaceDescriptionService() {};
    std::string summaryDescription(const std::string& Latitude, const std::string& Longitude) const;

private:
    std::string createGetRequestUrl(const std::string& Latitude, const std::string& Longitude) const;
    std::string summaryDescription(const Address& Address) const;
    std::string keyValue(const std::string& Key, const std::string& Value) const;
    std::string get(const std::string& RequestUrl) const;
    std::string summaryDescription(const std::string& Response) const;

protected:
    virtual std::shared_ptr<Http> httpService() const;
};