#ifndef MIGRATION_OFFICE_PERSONQUEUE_H
#define MIGRATION_OFFICE_PERSONQUEUE_H

#include "src/main/common/Person.h"
#include "src/main/common/Spawnables.h"

class PersonsGenerator {

    private:
        Spawnables persons;

    public:
        explicit PersonsGenerator(const std::string& people_file_path);
        Spawnables& get_persons();
        virtual ~PersonsGenerator() = default;

};


#endif //MIGRATION_OFFICE_PERSONQUEUE_H
