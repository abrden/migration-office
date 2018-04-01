#include "MinisterOfSecurity.h"

#include <fstream>
#include <sstream>
#include <iostream>

MinisterOfSecurity::MinisterOfSecurity(const std::string& alerts_file_path) : Spawner(alerts_file_path) {}

std::list<std::pair<int, Spawnable*>> MinisterOfSecurity::load_items(const std::string& alerts_file_path) {
    std::ifstream ifs(alerts_file_path);
    std::string line;

    while (getline(ifs, line)) {

        std::list<Feature*> wanted_person_features;

        std::stringstream ss(line);
        std::string feature_str;

        getline(ss, feature_str, ',');
        int timestamp = stoi(feature_str);

        while (getline(ss, feature_str, ','))  {
            Feature* feature = new Feature(feature_str);
            wanted_person_features.push_back(feature);
        }

        items.emplace_back(std::make_pair(timestamp, new WantedPersonAlert(wanted_person_features)));
    }

    return items;
}

MinisterOfSecurity::~MinisterOfSecurity() {}