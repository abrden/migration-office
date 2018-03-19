#include "Feature.h"

Feature::Feature(std::string feature) : feature(feature) {}

const std::string Feature::getFeature() {
    return feature;
}

Feature::~Feature() {}