#include "Foreigner.h"

Foreigner::Foreigner(const std::string& passport_id, std::list<Feature*>& features) :
        Person(features), passport(passport_id) {}

Passport& Foreigner::get_passport() {
    return passport;
}

bool Foreigner::has_id() {
    return false;
}