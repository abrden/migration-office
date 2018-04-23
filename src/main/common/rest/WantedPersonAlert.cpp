#include "WantedPersonAlert.h"

WantedPersonAlert::WantedPersonAlert(const std::list<Feature*>& person_features, const size_t id)
        : person_features(person_features), id(id) {}

const std::list<Feature*>& WantedPersonAlert::get_features() {
    return person_features;
}

size_t WantedPersonAlert::get_id() {
    return id;
}

WantedPersonAlert::~WantedPersonAlert() {
    while (!person_features.empty()) {
        delete person_features.back();
        person_features.pop_back();
    }
}