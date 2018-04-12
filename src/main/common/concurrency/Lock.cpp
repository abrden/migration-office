#include "Lock.h"

#include "unistd.h"

Lock::Lock(const std::string name) : name(name) {}

int Lock::unlock() {
    this->fl.l_type = F_UNLCK;
    return fcntl(this->fd, F_SETLK, &(this->fl));
}

Lock::~Lock() {
    close(this->fd);
}