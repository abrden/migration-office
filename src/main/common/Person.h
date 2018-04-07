#ifndef MIGRATION_OFFICE_PERSON_H
#define MIGRATION_OFFICE_PERSON_H

#include <list>
#include "Feature.h"
#include "Spawnable.h"

class Person : public Spawnable {

    private:
        std::list<Feature*> features;

    public:
        explicit Person(std::list<Feature*> features);
        std::list<Feature*> get_features();
        virtual bool has_id() = 0;
        ~Person();

};

#endif //MIGRATION_OFFICE_PERSON_H
