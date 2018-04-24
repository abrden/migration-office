#include "Passport.h"

Passport::Passport(const std::string& id) : id(id) {}

void Passport::stamp_passport() {}

const std::string& Passport::get_id() {
    return id;
}

Passport::~Passport() = default;