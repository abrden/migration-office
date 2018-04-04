#include "Foreigner.h"

Foreigner::Foreigner(Passport passport, std::list<Feature*> features) :
        Person(features), passport(passport) {}

const Passport Foreigner::getPassport() {
    return passport;
}

bool Foreigner::hasId() {
    return false;
}

Foreigner::~Foreigner() {}