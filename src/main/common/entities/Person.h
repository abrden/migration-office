#ifndef MIGRATION_OFFICE_PERSON_H
#define MIGRATION_OFFICE_PERSON_H

#include <list>
#include "Feature.h"

class Person {

    private:
        std::list<std::string> features;

    public:
        explicit Person(std::list<std::string> features);
        std::list<std::string> get_features();
        virtual bool has_id() = 0;
        virtual ~Person();

};

#endif //MIGRATION_OFFICE_PERSON_H
