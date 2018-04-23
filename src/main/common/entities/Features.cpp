#include "Features.h"

Features::Features(const std::list<std::string>& features) : features(features) {}

bool Features::operator==(const Features& other) const {
    std::list<std::string> features_sorted;
    std::copy(features.begin(), features.end(), std::back_inserter(features_sorted));

    std::list<std::string> other_features_sorted;
    std::copy(other.features.begin(), other.features.end(), std::back_inserter(other_features_sorted));

    return features_sorted == other_features_sorted;
}

Features::~Features() = default;
