#include <iostream>
#include <fstream>
#include <list>
#include "Feature.h"
#include "WantedPersonAlert.h"

std::list<std::string> init_fugitives_list() {
    std::ifstream ifs("../resources/fugitives.txt");
    std::list<std::string> fugitivesList;
    std::string fugitiveId;

    while (getline(ifs, fugitiveId)) {
        fugitivesList.emplace_back(fugitiveId);
    }
    return fugitivesList;
}

std::list<WantedPersonAlert> init_features_list() {
    std::ifstream ifs("../resources/alerts.txt");
    std::list<WantedPersonAlert> alerts;
    std::string line;

    while (getline(ifs, line)) {
        std::cout << line << std::endl;
        std::list<Feature> wantedPersonFeatures;
        //Feature
        alerts.emplace_back(wantedPersonFeatures);
    }
    return alerts;
}

void init_people() {
    // TODO
}

int main(int argc, char* argv[]) {
    std::cout << "Hello, World! This is the Conculandia Migration Office." << std::endl;
    init_fugitives_list();
    return 0;
}