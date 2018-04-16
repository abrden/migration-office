#ifndef MIGRATION_OFFICE_PERSONSQUEUE_H
#define MIGRATION_OFFICE_PERSONSQUEUE_H

#include "FifoReader.h"
#include "Queue.h"
#include "PersonMessage.h"
#include "Person.h"

class PersonsQueue {

    private:
        FifoReader fifo;

    public:
        PersonsQueue();
        bool empty();
        Person* front();

};


#endif //MIGRATION_OFFICE_PERSONSQUEUE_H
