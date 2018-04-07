#include "WantedPersonAlert.h"

WantedPersonAlert::WantedPersonAlert(const std::list<Feature*>& person_features) : person_features(person_features) {}

const std::list<Feature*>& WantedPersonAlert::get_features() {
    return person_features;
}

WantedPersonAlert::~WantedPersonAlert() {
    while (!person_features.empty()) {
        delete person_features.back();
        person_features.pop_back();
    }
}