#include <iostream>
#include <getopt.h>

const static int DEFAULT_BOOTHS_NUMBER = 10;
const static int DEFAULT_STAMPERS_NUMBER = 5;
const static std::string DEFAULT_LOG = "log";

enum ERRORS {
   NO_CONFIG_FILE = 1
};

int main(int argc, char *argv[]) {

    bool booths, stampers, people, alerts, fugitives, debug, log;
    booths = stampers = people = alerts = fugitives = debug = log = false;
    int booths_number = DEFAULT_BOOTHS_NUMBER;
    int stampers_number = DEFAULT_STAMPERS_NUMBER;
    std::string people_file, alerts_file, fugitives_file, log_file;
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

    while ((flag = getopt_long(argc, argv, "b:s:p:a:f:dl:", opts, NULL)) != -1) {
        switch (flag) {
            case 'b' :
                booths = true;
                booths_number = std::stoi(optarg);
                break;
            case 's' :
                stampers = true;
                stampers_number = std::stoi(optarg);
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
        return ERRORS::NO_CONFIG_FILE;
    }

    if (!log) {
        // TODO Log: No log path, using default
    }

    std::cout << "Welcome to the Conculandia Migration Office!" << std::endl;
    std::cout << "booths number = " << booths_number << std::endl;
    std::cout << "stampers number = " << stampers_number << std::endl;
    std::cout << "people file = " << people_file << std::endl;
    std::cout << "alerts file = " << alerts_file << std::endl;
    std::cout << "fugitives file = " << fugitives_file << std::endl;
    std::cout << "debug = " << debug << std::endl;
    std::cout << "log file = " << log_file << std::endl;

    exit(0);
}