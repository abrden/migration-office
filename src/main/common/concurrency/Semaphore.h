#ifndef MIGRATION_OFFICE_SEMAPHORE_H
#define MIGRATION_OFFICE_SEMAPHORE_H

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <string>

class Semaphore {

    private:
        int id;
        int initial_value;

        int init() const;

    public:
        Semaphore(const std::string& file, const char letter, const int initial_value);
        ~Semaphore();
        int p() const;
        int v() const;

};

#endif //MIGRATION_OFFICE_SEMAPHORE_H
