#include <iostream>
#include <getopt.h>

#include "MigrationOffice.h"

const static int DEFAULT_BOOTHS_NUMBER = 10;
const static int DEFAULT_STAMPERS_NUMBER = 5;
const static std::string DEFAULT_LOG = "log";

enum ERRORS {
   NO_CONFIG_FILE = 1
};

int read_arguments(int argc, char *argv[], int& booths_number, int& stampers_number,
                   std::string& people_file, std::string& alerts_file, std::string& fugitives_file,
                   bool& debug, std::string& log_file) {

    bool booths, stampers, people, alerts, fugitives, log;
    booths = stampers = people = alerts = fugitives = debug = log = false;
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
                booths = true;
                booths_number = std::stoi(optarg);
                // TODO handle invalid conversion exception
                break;
            case 's' :
                stampers = true;
                stampers_number = std::stoi(optarg);
                // TODO handle invalid conversion exception
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
                log = true;
                log_file = optarg;
                break;

                // TODO: handle default case
        }
    }

    if (!booths) {
        // TODO Log: No booths number, using default
    }

    if (!stampers) {
        // TODO Log: No stampers number, using default
    }

    if (!people || !alerts || !fugitives) {
        std::cerr << "fatal: Configuration file missing" << std::endl;
        return ERRORS::NO_CONFIG_FILE; // TODO set errno
    }

    if (!log) {
        // TODO Log: No log path, using default
    }

    return 0;
}

int main(int argc, char *argv[]) {
    bool debug;
    int booths_number;
    int stampers_number;
    std::string people_file, alerts_file, fugitives_file, log_file;

    int err = read_arguments(argc, argv, booths_number, stampers_number, people_file, alerts_file, fugitives_file, debug, log_file);
    if (err) exit(err); //FIXME

    MigrationOffice office(booths_number, stampers_number, people_file, alerts_file, fugitives_file, debug, log_file);

    std::cout << "Welcome to the Conculandia Migration Office!" << std::endl;
    std::cout << "booths number = " << booths_number << std::endl;
    std::cout << "stampers number = " << stampers_number << std::endl;
    std::cout << "people file = " << people_file << std::endl;
    std::cout << "alerts file = " << alerts_file << std::endl;
    std::cout << "fugitives file = " << fugitives_file << std::endl;
    std::cout << "debug = " << debug << std::endl;
    std::cout << "log file = " << log_file << std::endl;

    office.open_booths();

    office.wait_booths();

    return 0;
}