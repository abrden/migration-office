#include <iostream>
#include <getopt.h>

#include "MigrationOffice.h"

const static int DEFAULT_BOOTHS_NUMBER = 10;
const static int DEFAULT_STAMPERS_NUMBER = 5;
const static std::string DEFAULT_LOG = "log";

enum ERRORS {
    NO_CONFIG_FILE = -1,
    INVALID_BOOTHS_NUMBER = -2,
    INVALID_STAMPERS_NUMBER = -3
};

int read_arguments(int argc, char *argv[], int& booths_number, int& stampers_number,
                   std::string& people_file, std::string& alerts_file, std::string& fugitives_file,
                   bool& debug, std::string& log_file) {

    bool people, alerts, fugitives;
    people = alerts = fugitives = debug = false;
    booths_number = DEFAULT_BOOTHS_NUMBER;
    stampers_number = DEFAULT_STAMPERS_NUMBER;
    log_file = DEFAULT_LOG;

    int flag = 0;
    struct option opts[] = {
            {"booths", required_argument, 0, 'b'},
            {"stampers", required_argument, 0, 's'},
            {"debug", no_argument, 0, 'd'},
            {"people", required_argument, 0, 'p'},
            {"alerts", required_argument, 0, 'a'},
            {"fugitives", required_argument, 0, 'f'},
            {"log", required_argument, 0, 'l'}
    };

    while ((flag = getopt_long(argc, argv, "b:s:p:a:f:dl:", opts, nullptr)) != -1) {
        switch (flag) {
            case 'b' :
                try {
                    booths_number = std::stoi(optarg);
                }
                catch(std::invalid_argument& e){
                    std::cerr << "fatal: Invalid booths number" << std::endl;
                    return ERRORS::INVALID_BOOTHS_NUMBER;
                }
                break;
            case 's' :
                try {
                    stampers_number = std::stoi(optarg);
                }
                catch(std::invalid_argument& e){
                    std::cerr << "fatal: Invalid stampers number" << std::endl;
                    return ERRORS::INVALID_STAMPERS_NUMBER;
                }
                break;
            case 'p' :
                people = true;
                people_file = optarg;
                break;
            case 'a' :
                alerts = true;
                alerts_file = optarg;
                break;
            case 'f' :
                fugitives = true;
                fugitives_file = optarg;
                break;
            case 'd' :
                debug = true;
                break;
            case 'l' :
                log_file = optarg;
                break;
        }
    }

    if (!people || !alerts || !fugitives) {
        std::cerr << "fatal: Configuration file missing" << std::endl;
        return ERRORS::NO_CONFIG_FILE;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    bool debug;
    int booths_number;
    int stampers_number;
    std::string people_file, alerts_file, fugitives_file, log_file;

    int ans = read_arguments(argc, argv, booths_number, stampers_number, people_file, alerts_file, fugitives_file, debug, log_file);
    if (ans < 0) return ans;

    MigrationOffice office(booths_number, stampers_number, people_file, alerts_file, fugitives_file, debug, log_file);

    office.start();

    return 0;
}