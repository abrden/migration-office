#ifndef MIGRATION_OFFICE_PERSONSQUEUE_H
#define MIGRATION_OFFICE_PERSONSQUEUE_H


#include "PipeReader.h"
#include "Person.h"

class PersonsQueue {

    private:
        PipeReader pipe;

    public:
        bool empty();
        Person* front();

};


#endif //MIGRATION_OFFICE_PERSONSQUEUE_H
