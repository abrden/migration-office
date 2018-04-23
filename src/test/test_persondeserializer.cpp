#include "Foreigner.h"
#include "PersonDeserializer.h"
#include "Resident.h"
#include "Features.h"
#include "catch.hpp"

TEST_CASE("PersonDeserializer") {
    std::string serialized_agus = "1,38464269,,tez blanca,ojos oscuros";
    Person* agus = PersonDeserializer::deserialize(serialized_agus);

    REQUIRE(agus->has_id());

    REQUIRE(((Resident*)agus)->get_id() == 38464269);

    std::list<std::string> features;
    features.emplace_back("tez blanca");
    features.emplace_back("ojos oscuros");
    Features expected(features);
    REQUIRE(agus->get_features() == expected);

    delete agus;

    std::string serialized_bear = "0,1234567,PORTOÑOL123,tez blanca,ojos verdes,barbudo";
    Person* bear = PersonDeserializer::deserialize(serialized_bear);

    REQUIRE(!bear->has_id());

    REQUIRE(((Foreigner*)bear)->get_passport().get_id() == "PORTOÑOL123");

    std::list<std::string> features2;
    features2.emplace_back("tez blanca");
    features2.emplace_back("ojos verdes");
    features2.emplace_back("barbudo");
    Features expected2(features2);
    REQUIRE(bear->get_features() == expected2);

    delete bear;
}