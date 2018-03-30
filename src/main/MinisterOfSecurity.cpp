#include "MinisterOfSecurity.h"

#include <fstream>
#include <sstream>

bool order_by_timestamp(const WantedPersonAlert* first, const WantedPersonAlert* second) {
    return first->get_timestamp() <= second->get_timestamp();
}

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

    alerts.sort(order_by_timestamp);
}

std::list<WantedPersonAlert*> MinisterOfSecurity::get_alerts() {
    return alerts;
}

MinisterOfSecurity::~MinisterOfSecurity() {
    while (!alerts.empty()) delete alerts.back();
}