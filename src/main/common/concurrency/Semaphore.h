#ifndef MIGRATION_OFFICE_SEMAPHORE_H
#define MIGRATION_OFFICE_SEMAPHORE_H

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <string>

class Semaphore {

    private:
        int id;

    public:
        Semaphore(const std::string& file, const char letter);
        ~Semaphore();
        int init(const int initial_value) const;
        int p() const;
        int v() const;
        int w() const;

};

#endif //MIGRATION_OFFICE_SEMAPHORE_H
