#include "Spawner.h"
#include "MinisterOfSecurity.h"
#include "catch.hpp"
#include <list>

TEST_CASE("Spawner sort") {
    MinisterOfSecurity m("../resources/alerts.txt");
    Alerts& a = m.get_alerts();
    Spawner s(a);
    REQUIRE(a.get_items().front().first == 0);
    REQUIRE(a.get_items().back().first == 4);
}

TEST_CASE("Spawner run") {
    MinisterOfSecurity m("../resources/alerts.txt");
    Alerts& a = m.get_alerts();
    Spawner s(a);
    s.run();
}