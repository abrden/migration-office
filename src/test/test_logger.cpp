#include <unistd.h>
#include <iostream>
#include "Logger.h"
#include "catch.hpp"

const static std::string LOG_FILE = "../resources/testlog.txt";
const static int BUFFSIZE = 200;

TEST_CASE("Logger") {

    /* FIXME uninitialised values
    SECTION("Log string") {
        Logger l(true, LOG_FILE);
        std::string line = "hi log!";
        l << line << std::endl;

        std::ostringstream expected;
        expected << "[" << getpid() << "] " << line;

        int fd = open(LOG_FILE.c_str(), O_RDONLY);

        char buffer[BUFFSIZE];
        ssize_t bytes_read = read(fd, buffer, sizeof(char) * expected.str().size());
        REQUIRE(bytes_read == expected.str().size());

        std::string buffer_read(buffer);
        REQUIRE(buffer_read.compare(expected.str()) == 0);

        close(fd);
        unlink(LOG_FILE.c_str());
    }
    */

    SECTION("Debug false") {
        Logger l(false, LOG_FILE);
        std::string line = "hi log!";
        l << line << std::endl;
    }


    /*SECTION("Log string") {
        Logger l(true, LOG_FILE);
        std::string line = "hi im logging a number: ";
        ssize_t bytes = 45;
        l << "[TESTS] " << line << bytes << std::endl;

        int fd = open(LOG_FILE.c_str(), O_RDONLY);
        char buffer[34];
        ssize_t bytes_read = read(fd, buffer, sizeof(char) * 34);
        REQUIRE(bytes_read == 34);
        std::string buffer_read(buffer);
        std::string expected("[TESTS] hi im logging a number: 45");
        REQUIRE(buffer_read.compare(expected) == 0);
        close(fd);
        unlink(LOG_FILE.c_str());
    }*/

}