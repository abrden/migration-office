#include "Features.h"
#include "catch.hpp"

TEST_CASE("Features") {
    std::list<std::string> features1;
    features1.emplace_back("tez blanca");
    features1.emplace_back("ojos oscuros");
    Features features_a(features1);
    Features features_a2(features1);

    std::list<std::string> features2;
    features2.emplace_back("ojos oscuros");
    features2.emplace_back("tez blanca");
    Features features_b(features2);

    REQUIRE(features_a == features_a2);
    REQUIRE(features_a == features_b);
}