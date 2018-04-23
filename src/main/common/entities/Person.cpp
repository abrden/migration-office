#include "Person.h"

Person::Person(const std::list<std::string>& features) : features(features) {}

Features& Person::get_features() {
    return features;
}

Person::~Person() = default;