#ifndef MIGRATION_OFFICE_PERSONSQUEUE_H
#define MIGRATION_OFFICE_PERSONSQUEUE_H

#include "ExclusiveLock.h"
#include "FifoReader.h"
#include "Person.h"

class PersonsQueue {

    private:
        FifoReader fifo;
        ExclusiveLock fifo_lock;

    public:
        PersonsQueue();
        Person* front();

};


#endif //MIGRATION_OFFICE_PERSONSQUEUE_H
