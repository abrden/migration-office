#ifndef MIGRATION_OFFICE_PERSON_H
#define MIGRATION_OFFICE_PERSON_H

#include <list>
#include "Features.h"

class Person {

    private:
        Features features;

    public:
        explicit Person(std::list<std::string> features);
        Features& get_features();
        virtual bool has_id() = 0;
        virtual ~Person();

};

#endif //MIGRATION_OFFICE_PERSON_H
