#include "Foreigner.h"

Foreigner::Foreigner(Passport passport, std::list<Feature*> features) :
        Person(features), passport(passport) {}

Passport& Foreigner::get_passport() {
    return passport;
}

bool Foreigner::has_id() {
    return false;
}