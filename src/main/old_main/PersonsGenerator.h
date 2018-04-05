#ifndef MIGRATION_OFFICE_PERSONQUEUE_H
#define MIGRATION_OFFICE_PERSONQUEUE_H

#include "Person.h"
#include "Spawnables.h"

#include <queue>

class PersonsGenerator {

private:
    Spawnables persons;

public:
    explicit PersonsGenerator(const std::string& persons_file_path);
    
    Spawnables& get_persons();
    
    virtual ~PersonsGenerator() = default;
};


#endif //MIGRATION_OFFICE_PERSONQUEUE_H
