#include "ExclusiveLock.h"

#include "unistd.h"
#include <system_error>

ExclusiveLock::ExclusiveLock(const std::string &name) : Lock(name) {
    this->fl.l_type = F_WRLCK;
    this->fl.l_whence = SEEK_SET;
    this->fl.l_start = 0;
    this->fl.l_len = 0;
    this->fd = open(this->name.c_str(), O_CREAT | O_WRONLY, 0777);
    if (this->fd == -1) {
        throw std::system_error(errno, std::generic_category());
    }
}

int ExclusiveLock::lock() {
    this->fl.l_type = F_WRLCK;
    int lock_fd = fcntl(this->fd, F_SETLKW, &(this->fl));
    if (lock_fd == -1) {
        throw std::system_error(errno, std::generic_category());
    }
    return lock_fd;
}
