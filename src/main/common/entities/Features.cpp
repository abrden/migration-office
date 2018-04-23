#include "Features.h"

Features::Features(std::list<std::string>& features) : features(features) {}

bool Features::operator==(const Features& other) const {
    return features == other.features;
}

Features::~Features() = default;
