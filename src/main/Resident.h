#ifndef MIGRATION_OFFICE_RESIDENT_H
#define MIGRATION_OFFICE_RESIDENT_H

#include "Person.h"

class Resident : public Person {

    private:
        const unsigned int id;
        const std::list<Feature*> features;

    public:
        Resident(unsigned int id, std::list<Feature*> features);
        unsigned int getId();
        bool hasId() override;
        ~Resident() override;

};

#endif //MIGRATION_OFFICE_RESIDENT_H
