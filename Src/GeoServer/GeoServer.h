#pragma once

#include "Area.h"
#include "Location.h"
#include "User.h"

#include <string>
#include <unordered_map>
#include <vector>

class GeoServer
{
public:
    void track(const std::string& user);
    void stopTracking(const std::string& user);
    void updateLocation(const std::string& user, const Location& location);

    bool isTracking(const std::string& user) const;
    Location locationOf(const std::string& user) const;
    bool isDifferentUserInBounds(
        const std::pair<std::string, Location>& each, const std::string& user, const Area& box) const;
    std::vector<User> usersInBox(const std::string& user, double widthInMeters, double heightInMeters) const;

private:
    std::unordered_map<std::string, Location> locations_;

    std::unordered_map<std::string, Location>::const_iterator find(const std::string& user) const;
};
