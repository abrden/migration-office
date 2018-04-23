#include "WantedPersonAlert.h"

WantedPersonAlert::WantedPersonAlert(const std::list<std::string>& person_features, const size_t id)
        : person_features(person_features), id(id) {}

const std::list<std::string>& WantedPersonAlert::get_features() {
    return person_features;
}

size_t WantedPersonAlert::get_id() {
    return id;
}

WantedPersonAlert::~WantedPersonAlert() = default;