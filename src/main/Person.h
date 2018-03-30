#ifndef MIGRATION_OFFICE_PERSON_H
#define MIGRATION_OFFICE_PERSON_H

#include <list>
#include "Feature.h"

class Person {

    protected:
        std::list<Feature*> features;

    public:
        Person(std::list<Feature*> features);
        std::list<Feature*> getFeatures();
        virtual bool hasId() = 0;
        virtual ~Person();

};

#endif //MIGRATION_OFFICE_PERSON_H
