#include "ConfigurationFileReader.h"
#include "catch.hpp"

TEST_CASE("ConfigurationFileReader") {
    Spawnables s;
    ConfigurationFileReader::load_persons("../resources/people.txt", s);
    std::list<std::pair<int, std::string>> serialized_people = s.get_items();
    REQUIRE(serialized_people.front().first == 5);
    REQUIRE(serialized_people.front().second == "1,38464269,,tez blanca,ojos oscuros");
    REQUIRE(serialized_people.back().first == 10);
    REQUIRE(serialized_people.back().second == "0,,NOCRIMINAL,petiso,orejudo");
}