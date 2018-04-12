#ifndef MIGRATION_OFFICE_PERSONSQUEUE_H
#define MIGRATION_OFFICE_PERSONSQUEUE_H


#include "Pipe.h"
#include "Person.h"

class PersonsQueue {

    private:
        Pipe pipe;

    public:
        bool empty();
        Person* front();

};


#endif //MIGRATION_OFFICE_PERSONSQUEUE_H
