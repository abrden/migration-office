#ifndef MIGRATION_OFFICE_PERSONSQUEUE_H
#define MIGRATION_OFFICE_PERSONSQUEUE_H

#include "ExclusiveLock.h"
#include "FifoReader.h"
#include "Person.h"
#include "Logger.h"

class PersonsQueue {

    private:
        Logger& logger;

        FifoReader fifo;
        ExclusiveLock fifo_lock;

    public:
        explicit PersonsQueue(Logger& logger);
        Person* front();

};


#endif //MIGRATION_OFFICE_PERSONSQUEUE_H
