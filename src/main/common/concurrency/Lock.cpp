#include "Lock.h"

#include "unistd.h"
#include <system_error>

Lock::Lock(const std::string& name) : name(name) {}

int Lock::unlock() {
    fl.l_type = F_UNLCK;
    int unlock_fd = fcntl(fd, F_SETLK, &(fl));
    if (unlock_fd == -1) {
        throw std::system_error(errno, std::generic_category());
    }
    return unlock_fd;
}

Lock::~Lock() {
    close(fd);
}