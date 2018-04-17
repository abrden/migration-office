#include "Spawner.h"
#include "MinisterOfSecurity.h"

#include "catch.hpp"
#include <list>
//#include "PeopleSpawner.h"

/*
TEST_CASE("Spawner sort") {

    SECTION("security alerts") {
        MinisterOfSecurity m("../resources/alerts.txt");
        Spawnables& a = m.get_alerts();
        Spawner s(a);

        REQUIRE(a.get_items().front().first == 0);
        REQUIRE(a.get_items().back().first == 4);
    }

    SECTION("persons") {
        PersonsGenerator pg("../resources/people.txt");
        Spawnables& p = pg.get_persons();
        Spawner s(p);

        REQUIRE(p.get_items().front().first == 2);
        REQUIRE(p.get_items().back().first == 5);
    }
}

TEST_CASE("Spawner run") {

    SECTION("with security alerts") {
        MinisterOfSecurity m("../resources/alerts.txt");
        Spawnables& a = m.get_alerts();
        Spawner s(a);

        s.run();
    }

    SECTION("with persons") {
        PersonsGenerator pg("../resources/people.txt");
        Spawnables& p = pg.get_persons();
        Spawner s(p);

        s.run();
    }
}
*/