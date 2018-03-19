#ifndef MIGRATION_OFFICE_PERSON_H
#define MIGRATION_OFFICE_PERSON_H

#include <list>
#include "Passport.h"
#include "Feature.h"

class Person {

    private:
        const unsigned int id;
        const Passport passport;
        const bool resident;
        const std::list<Feature> features;

    public:
        Person(unsigned int dni, Passport passport, bool resident, std::list<Feature> features);
        const unsigned int getId();
        bool isResident();
        const std::list<Feature> getFeatures();
        ~Person();

};

#endif //MIGRATION_OFFICE_PERSON_H
