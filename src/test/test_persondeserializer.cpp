#include <src/main/common/entities/Foreigner.h>
#include "PersonDeserializer.h"
#include "Resident.h"
#include "catch.hpp"

TEST_CASE("PersonDeserializer") {
    std::string serialized_agus = "1,38464269,,tez blanca,ojos oscuros";
    Person* agus = PersonDeserializer::deserialize(serialized_agus);
    REQUIRE(agus->has_id());
    REQUIRE(((Resident*)agus)->get_id() == 38464269);
    REQUIRE(agus->get_features().front() == "tez blanca");
    delete agus;

    std::string serialized_bear = "0,1234567,PORTOÑOL123,tez blanca,ojos verdes,barbudo";
    Person* bear = PersonDeserializer::deserialize(serialized_bear);
    REQUIRE(!bear->has_id());
    REQUIRE(((Foreigner*)bear)->get_passport().get_id() == "PORTOÑOL123");
    REQUIRE(bear->get_features().back() == "barbudo");

    delete bear;
}