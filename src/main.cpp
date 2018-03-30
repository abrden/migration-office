#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include "Feature.h"
#include "WantedPersonAlert.h"

std::list<std::string> init_fugitives_list() {
    std::ifstream ifs("../resources/fugitives.txt");
    std::list<std::string> fugitives_list;
    std::string fugitive_id;

    while (getline(ifs, fugitive_id)) {
        fugitives_list.emplace_back(fugitive_id);
    }
    return fugitives_list;
}

std::list<WantedPersonAlert*> init_wanted_alerts_list() {
    std::ifstream ifs("../resources/alerts.txt");
    std::list<WantedPersonAlert*> alerts;
    std::string line;

    while (getline(ifs, line)) {

        std::list<Feature*> wanted_person_features;

        std::stringstream ss(line);
        std::string feature_str;

        getline(ss, feature_str, ',');
        int timestamp = stoi(feature_str);

        while (getline(ss, feature_str, ','))  {
            Feature* feature = new Feature(feature_str);
            wanted_person_features.emplace_back(feature);
        }

        alerts.emplace_back(new WantedPersonAlert(timestamp, wanted_person_features));
    }

    return alerts;
}

void init_people() {
    // TODO
}

int main(int argc, char* argv[]) {
    std::cout << "Hello, World! This is the Conculandia Migration Office." << std::endl;
    return 0;
}