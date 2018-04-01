#include "Spawner.h"
#include "MinisterOfSecurity.h"
#include "catch.hpp"
#include <list>

TEST_CASE("Spawner", "[feature]") {
    MinisterOfSecurity m("../resources/alerts.txt");
    std::list<std::pair<int, Spawnable*>>& wpa = m.get_alerts();
    Spawner s(wpa);
    REQUIRE(wpa.size() == 3);
}