#ifndef MIGRATION_OFFICE_PERSONSERIALIZER_H
#define MIGRATION_OFFICE_PERSONSERIALIZER_H


#include "Person.h"

class PersonSerializer {

    public:
        static char* serialize(Person* person);

};


#endif //MIGRATION_OFFICE_PERSONSERIALIZER_H
