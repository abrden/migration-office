#include "Resident.h"

Resident::Resident(unsigned int id, std::list<Feature*> features) :
        Person(features), id(id) {}

unsigned int Resident::getId() {
    return id;
}

bool Resident::hasId() {
    return true;
}

Resident::~Resident() {}