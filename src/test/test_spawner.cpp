#include "Spawner.h"
#include "MinisterOfSecurity.h"
#include "catch.hpp"
#include <list>

TEST_CASE("Spawner", "[feature]") {
    MinisterOfSecurity m("../resources/alerts.txt");
    std::list<std::pair<int, WantedPersonAlert*>>& wpa = m.get_alerts();
    Spawner<WantedPersonAlert> s(wpa);
    REQUIRE(wpa.front().first == 0);
    REQUIRE(wpa.back().first == 4);
}