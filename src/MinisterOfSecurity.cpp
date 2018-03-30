#include "MinisterOfSecurity.h"

#include <fstream>
#include <sstream>

MinisterOfSecurity::MinisterOfSecurity(const std::string& alerts_file_path) {
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

        alerts.push_back(new WantedPersonAlert(timestamp, wanted_person_features));
    }
}

MinisterOfSecurity::~MinisterOfSecurity() {
    while (!alerts.empty()) delete alerts.back();
}