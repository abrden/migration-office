#include "Person.h"

Person::Person(unsigned int dni, Passport passport, bool resident, std::list<Feature> features) :
        id(id), passport(passport), resident(resident), features(features) {}

const unsigned int Person::getId() {
    return id;
}

bool Person::isResident() {
    return resident;
}

const std::list<Feature> Person::getFeatures() {
    return features;
}

Person::~Person() {}