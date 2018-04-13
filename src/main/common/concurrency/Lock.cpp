#include "Lock.h"

#include "unistd.h"
#include <system_error>

Lock::Lock(const std::string &name) : name(name) {}

int Lock::unlock() {
    this->fl.l_type = F_UNLCK;
    int unlock_fd = fcntl(this->fd, F_SETLK, &(this->fl));
    if (unlock_fd == -1) {
        throw std::system_error(errno, std::generic_category());
    }
    return unlock_fd;
}

Lock::~Lock() {
    close(this->fd);
}