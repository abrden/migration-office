#include "WantedPersonAlert.h"

WantedPersonAlert::WantedPersonAlert(const int timestamp, const std::list<Feature*>& person_features) : timestamp(timestamp),
                                                                                                       person_features(person_features) {}

const std::list<Feature*> WantedPersonAlert::get_features() {
    return person_features;
}

const int WantedPersonAlert::get_timestamp() {
    return timestamp;
}

WantedPersonAlert::~WantedPersonAlert() {
    while (!person_features.empty()) delete person_features.back();
}