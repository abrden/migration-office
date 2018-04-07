#include "src/main/common/PersonsGenerator.h"

#include "catch.hpp"

TEST_CASE("PersonsGenerator") {
    PersonsGenerator pg("../resources/people.txt");
    Spawnables& persons = pg.get_persons();

    REQUIRE(persons.get_items().size() == 2);
}