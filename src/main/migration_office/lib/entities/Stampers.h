#ifndef MIGRATION_OFFICE_STAMPERS_H
#define MIGRATION_OFFICE_STAMPERS_H


#include "Semaphore.h"

class Stampers {

    private:
        Semaphore stampers;

    public:
        Stampers(const int stampers_number);
        ~Stampers();

};


#endif //MIGRATION_OFFICE_STAMPERS_H
