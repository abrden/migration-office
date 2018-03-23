#include "WantedPersonAlert.h"

WantedPersonAlert::WantedPersonAlert(std::list<Feature> personFeatures) : personFeatures(personFeatures) {}

const std::list<Feature> WantedPersonAlert::getFeatures() {
    return personFeatures;
}

WantedPersonAlert::~WantedPersonAlert() {}