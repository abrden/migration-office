#ifndef MIGRATION_OFFICE_PERSONSQUEUE_H
#define MIGRATION_OFFICE_PERSONSQUEUE_H

#include "Queue.h"
#include "Message.h"
#include "Person.h"

class PersonsQueue {

    private:
        Queue<message> queue;

    public:
        PersonsQueue();
        bool empty();
        Person* front();

};


#endif //MIGRATION_OFFICE_PERSONSQUEUE_H
