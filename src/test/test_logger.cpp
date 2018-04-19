#include "Logger.h"
#include "catch.hpp"

TEST_CASE("Logger") {
    Logger l("../resources/testlog.txt");
    l << "hi log!" << std::endl;
}