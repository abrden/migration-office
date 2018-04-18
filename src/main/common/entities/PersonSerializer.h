#ifndef MIGRATION_OFFICE_PERSONSERIALIZER_H
#define MIGRATION_OFFICE_PERSONSERIALIZER_H


#include "Person.h"

#include <string>

class PersonSerializer {

    public:
        static std::string serialize(Person* person);

};


#endif //MIGRATION_OFFICE_PERSONSERIALIZER_H
