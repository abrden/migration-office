#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include "MinisterOfSecurity.h"

std::list<std::string> init_fugitives_list() {
    std::ifstream ifs("../resources/fugitives.txt");
    std::list<std::string> fugitives_list;
    std::string fugitive_id;

    while (getline(ifs, fugitive_id)) {
        fugitives_list.emplace_back(fugitive_id);
    }
    return fugitives_list;
}


int main(int argc, char* argv[]) {
    std::cout << "Hello, World! This is the Conculandia Migration Office." << std::endl;
    MinisterOfSecurity m("../resources/alerts.txt");
    std::list<WantedPersonAlert*> wpa = m.get_alerts();
    std::cout << wpa.size() << std::endl;
    return 0;
}