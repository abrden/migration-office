#include "PersonsGenerator.h"

#include "catch.hpp"

TEST_CASE("PersonsGenerator", "[feature]") {
    PersonsGenerator pg("../resources/people.txt");
    const std::queue<std::pair<unsigned int,Person*>> persons = pg.get_persons();

    REQUIRE(persons.size() == 2);
    REQUIRE(persons.front().first == 0);
    REQUIRE(persons.back().first == 1);
}