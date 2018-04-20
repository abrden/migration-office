#include <iostream>
#include <map>
#include "Statistics.h"

int main(int argc, char* argv[]) {
    std::cout << "Welcome to Conculandia's Statistics Department" << std::endl;
    Statistics s;

    std::string line;
    std::cout << "> ";
    std::getline(std::cin, line);
    while (line.compare("exit")) {
        if (!line.compare("allowed residents")) {
            std::cout << "Allowed residents: " << s.get_allowed_residents() << std::endl;
        } else if (!line.compare("detained residents")){
            std::cout << "Detained residents: " << s.get_detained_residents() << std::endl;
        } else if (!line.compare("allowed foreigners")) {
            std::cout << "Allowed foreigners: " << s.get_allowed_foreigners() << std::endl;
        } else if (!line.compare("deported foreigners")) {
            std::cout << "Deported foreigners: " << s.get_deported_foreigners() << std::endl;
        } else {
            std::cout << "Invalid command, try again" << std::endl;
        }
        std::cout << "> ";
        std::getline(std::cin, line);
    }
    return 0;
}