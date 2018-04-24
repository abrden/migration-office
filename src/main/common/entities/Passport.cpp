#include "Passport.h"

Passport::Passport(const std::string& id) : id(id) {}

void Passport::stamp_passport(Logger& logger) {
    logger(PASSPORT) << "Passport " << id << "stamped"<< std::endl;
}

const std::string& Passport::get_id() {
    return id;
}

Passport::~Passport() = default;