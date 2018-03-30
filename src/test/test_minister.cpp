#include "MinisterOfSecurity.h"
#include "catch.hpp"
#include <list>

TEST_CASE("Minister", "[feature]") {
    MinisterOfSecurity m("../resources/alerts.txt");
    std::list<WantedPersonAlert*> wpa = m.get_alerts();
    REQUIRE(wpa.size() == 3);
    REQUIRE(wpa.front()->get_timestamp() == 0);
    REQUIRE(wpa.back()->get_timestamp() == 4);
}