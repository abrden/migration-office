#include <iostream>
#include <fstream>
#include <sstream>
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

std::list<WantedPersonAlert*> init_wanted_alerts_list() {
    std::ifstream ifs("../resources/alerts.txt");
    std::list<WantedPersonAlert*> alerts;
    std::string line;

    while (getline(ifs, line)) {
        std::cout << line << std::endl;

        std::list<Feature*> wantedPersonFeatures;

        std::stringstream ss(line);
        std::string featureStr;

        while (getline(ss, featureStr, ','))  {
            std::cout << featureStr << std::endl;
            Feature* feature = new Feature(featureStr);
            wantedPersonFeatures.emplace_back(feature);
        }

        alerts.emplace_back(new WantedPersonAlert(wantedPersonFeatures)); // FIXME Move alert parse to WantedPersonAlert constructor
    }
    return alerts;
}

void init_people() {
    // TODO
}

int main(int argc, char* argv[]) {
    std::cout << "Hello, World! This is the Conculandia Migration Office." << std::endl;
    init_wanted_alerts_list();
    return 0;
}