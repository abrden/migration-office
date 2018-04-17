#ifndef MIGRATION_OFFICE_PERSONDESERIALIZER_H
#define MIGRATION_OFFICE_PERSONDESERIALIZER_H

#include <string>
#include "Person.h"

class PersonDeserializer {

    public:
        static Person* deserialize(std::string& serialized_person);

};


#endif //MIGRATION_OFFICE_PERSONDESERIALIZER_H
