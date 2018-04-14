#ifndef MIGRATION_OFFICE_PERSONSQUEUE_H
#define MIGRATION_OFFICE_PERSONSQUEUE_H

#include "Queue.h"
#include "PersonMessage.h"
#include "Person.h"

class PersonsQueue {

    private:
        Queue<person_message> queue;

    public:
        PersonsQueue();
        bool empty();
        Person* front();

};


#endif //MIGRATION_OFFICE_PERSONSQUEUE_H
