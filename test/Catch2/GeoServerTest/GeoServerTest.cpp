#include "GeoServer/GeoServer.h"
#include "GeoServer/User.h"
#include "GeoServer/VectorUtil.h"

#include <catch2/catch.hpp>
using namespace std;
using namespace Catch;

class Fixture
{
public:
    GeoServer m_server;
    const string m_aUser { "auser" };
    const double m_locationToLerance { 0.005 };
};

TEST_CASE_METHOD(Fixture, "Tracks m_aUser", "[AGeoServer]")
{
    m_server.track(m_aUser);
    REQUIRE(m_server.isTracking(m_aUser));
}

TEST_CASE_METHOD(Fixture, "Is not tracking m_aUser not tracked", "[AGeoServer]")
{
    REQUIRE_FALSE(m_server.isTracking(m_aUser));
}

TEST_CASE_METHOD(Fixture, "Tracks multiple users", "[AGeoServer]")
{
    m_server.track(m_aUser);
    m_server.track("anotheruser");
    REQUIRE_FALSE(m_server.isTracking("thirduser"));
    REQUIRE(m_server.isTracking(m_aUser));
    REQUIRE(m_server.isTracking("anotheruser"));
}

TEST_CASE_METHOD(Fixture, "Is tracking answers false when user no longer tracked", "[AGeoServer]")
{
    m_server.track(m_aUser);
    m_server.stopTracking(m_aUser);

    REQUIRE_FALSE(m_server.isTracking(m_aUser));
}

TEST_CASE_METHOD(Fixture, "Updates location of user", "[AGeoServer]")
{
    m_server.track(m_aUser);
    m_server.updateLocation(m_aUser, Location { 38, -104 });

    auto location = m_server.locationOf(m_aUser);
    REQUIRE(location.latitude() == 38);
    REQUIRE(location.longitude() == -104);
}

TEST_CASE_METHOD(Fixture, "Answers unknown location for user not tracked", "[AGeoServer]")
{
    REQUIRE(m_server.locationOf("anAbUser").isUnknown());
}

TEST_CASE_METHOD(Fixture, "Answers unknown location for tracked user with no location update", "[AGeoServer]")
{
    m_server.track(m_aUser);
    REQUIRE(m_server.locationOf(m_aUser).isUnknown());
}

TEST_CASE_METHOD(Fixture, "Answers unknown location for user no longer tracked", "[AGeoServer]")
{
    m_server.track(m_aUser);
    m_server.updateLocation(m_aUser, Location(40, 100));
    m_server.stopTracking(m_aUser);
    REQUIRE(m_server.locationOf(m_aUser).isUnknown());
}

class FixtureUserInBox
{
public:
    GeoServer server;
    const double TenMeters { 10 };
    const double Width { 2000 + TenMeters };
    const double Height { 4000 + TenMeters };
    const string aUser { "auser" };
    const string bUser { "buser" };
    const string cUser { "cuser" };
    Location aUserLocation { 38, -103 };
    FixtureUserInBox()
    {
        server.track(aUser);
        server.track(bUser);
        server.track(cUser);
        server.updateLocation(aUser, aUserLocation);
    }
    vector<string> UserNames(const vector<User>& users)
    {
        return Collect<User, string>(users, [](User each) { return each.name(); });
    };
};

TEST_CASE_METHOD(FixtureUserInBox, "Answers users in specified range", "[AGeoServer_UsersInBox]")
{
    server.updateLocation(bUser, Location { aUserLocation.go(Width / 2 - TenMeters, East) });

    auto users = server.usersInBox(aUser, Width, Height);

    REQUIRE_THAT(vector<string> { bUser }, Equals(UserNames(users)));
}

TEST_CASE_METHOD(FixtureUserInBox, "Answers only users within specified range", "[AGeoServer_UsersInBox]")
{
    server.updateLocation(bUser, Location { aUserLocation.go(Width / 2 + TenMeters, East) });

    server.updateLocation(cUser, Location { aUserLocation.go(Width / 2 - TenMeters, East) });

    auto users = server.usersInBox(aUser, Width, Height);

    REQUIRE_THAT(vector<string> { cUser }, Equals(UserNames(users)));
}