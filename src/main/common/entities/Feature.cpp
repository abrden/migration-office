#include "Feature.h"

Feature::Feature(std::string feature) : feature(feature) {}

const std::string& Feature::get_feature() {
    return feature;
}

Feature::~Feature() = default;
