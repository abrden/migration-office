#include "Person.h"

Person::Person(std::list<std::string> features) : features(features) {}

std::list<std::string> Person::get_features() {
    return features;
}

Person::~Person() = default;