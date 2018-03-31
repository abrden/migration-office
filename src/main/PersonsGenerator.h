#ifndef MIGRATION_OFFICE_PERSONQUEUE_H
#define MIGRATION_OFFICE_PERSONQUEUE_H

#include "Person.h"

#include <queue>

class PersonsGenerator {

private:
    std::queue<Person*> persons;

public:
    PersonsGenerator(const std::string& persons_file_path);

    virtual ~PersonsGenerator();
};


#endif //MIGRATION_OFFICE_PERSONQUEUE_H
