#include "Person.h"

Person::Person(std::list<Feature> features) : features(features) {}

const std::list<Feature> Person::getFeatures() {
    return features;
}

Person::~Person() {}