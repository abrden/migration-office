#ifndef MIGRATION_OFFICE_LOCK_H
#define MIGRATION_OFFICE_LOCK_H

#include <fcntl.h>
#include <string>

class Lock {

protected:
    struct flock fl;
    int fd;
    const std::string name;

public:
    explicit Lock(const std::string &name);

    virtual int lock() = 0;

    int unlock();

    ~Lock();
};


#endif //MIGRATION_OFFICE_LOCK_H
