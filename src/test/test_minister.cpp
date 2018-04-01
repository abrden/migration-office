#include "MinisterOfSecurity.h"
#include "catch.hpp"
#include <list>

TEST_CASE("Minister", "[feature]") {
    MinisterOfSecurity m("../resources/alerts.txt");
    std::list<std::pair<int, Spawnable*>>& wpa = m.get_alerts();
    REQUIRE(wpa.size() == 3);
}