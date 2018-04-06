#include "Resident.h"

Resident::Resident(unsigned int id, std::list<Feature*> features) :
        Person(features), id(id) {}

unsigned int Resident::get_id() {
    return id;
}

bool Resident::has_id() {
    return true;
}