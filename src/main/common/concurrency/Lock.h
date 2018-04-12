#ifndef MIGRATION_OFFICE_LOCK_H
#define MIGRATION_OFFICE_LOCK_H

//#include <unistd.h>
#include <fcntl.h>
#include <string>

class Lock {
  private:
    struct flock fl;
    int fd;
    std::string name;

  public:
    Lock(const std::string name);

    ~Lock();

    int lock();

    int unlock();

    ssize_t write(const void *buffer, const ssize_t buffsize) const;
};

#endif //MIGRATION_OFFICE_LOCK_H
