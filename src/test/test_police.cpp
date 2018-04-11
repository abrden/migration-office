#include "Police.h"
#include "Resident.h"
#include "Feature.h"

#include "catch.hpp"

// TODO
TEST_CASE("Police") {

    SECTION("is_fugitive") {
        SECTION("with non fugitive id") {
            Police p;
            const unsigned int FUGITIVE_ID = 123456789;
            std::list<Feature*> features = { new Feature("ojos verdes") };
            p.add_fugitive(FUGITIVE_ID);
            Resident r(987654321, features);

            REQUIRE(p.is_fugitive(&r) == false);
        }

        SECTION("with fugitive id", "[.]") {
            Police p;
            const unsigned int FUGITIVE_ID = 123456789;
            std::list<Feature*> features = { new Feature("ojos verdes") };
            p.add_fugitive(FUGITIVE_ID);
            Resident r(FUGITIVE_ID, features);

            REQUIRE(p.is_fugitive(&r) == true);
        }
    }

//    SECTION("is_wanted_person", ".") {
//        Police p;
//
//        REQUIRE(p != NULL);
//    }
}

