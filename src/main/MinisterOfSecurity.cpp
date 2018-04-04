#include "MinisterOfSecurity.h"

#include <fstream>
#include <sstream>
#include <iostream>

MinisterOfSecurity::MinisterOfSecurity(const std::string& alerts_file_path) {
    load_alerts(alerts_file_path);
}

void MinisterOfSecurity::load_alerts(const std::string& alerts_file_path) {
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

        alerts.push_spawnable(timestamp, new WantedPersonAlert(wanted_person_features));
    }
}

Spawnables& MinisterOfSecurity::get_alerts() {
    return alerts;
}
