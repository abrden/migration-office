#ifndef MIGRATION_OFFICE_RESIDENT_H
#define MIGRATION_OFFICE_RESIDENT_H

#include "Person.h"

class Resident : public Person {

    private:
        const unsigned int id;

    public:
        Resident(unsigned int id, std::list<std::string> features);
        unsigned int get_id();
        bool has_id() override;

};

#endif //MIGRATION_OFFICE_RESIDENT_H
