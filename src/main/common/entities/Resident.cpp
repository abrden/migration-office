#include "Resident.h"

Resident::Resident(unsigned int id, const std::list<std::string>& features) :
        Person(features), id(id) {}

unsigned int Resident::get_id() {
    return id;
}

bool Resident::has_id() {
    return true;
}