#include "catch.hpp"
#include <list>
#include "Feature.h"

TEST_CASE("Feature", "[feature]") {
    Feature f1("feature1");
    std::list<Feature> features = { f1 };
    REQUIRE(features.size() == 1);
}