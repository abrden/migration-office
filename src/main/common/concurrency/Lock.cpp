#include "unistd.h"

#include "Lock.h"

Lock::Lock(const std::string name) {

    this->name = name;
    this->fl.l_type = F_WRLCK;
    this->fl.l_whence = SEEK_SET;
    this->fl.l_start = 0;
    this->fl.l_len = 0;
    this->fd = open(this->name.c_str(), O_CREAT | O_WRONLY, 0777);
}

int Lock::lock() {
    this->fl.l_type = F_WRLCK;
    return fcntl(this->fd, F_SETLKW, &(this->fl));
}

int Lock::unlock() {
    this->fl.l_type = F_UNLCK;
    return fcntl(this->fd, F_SETLK, &(this->fl));
}

ssize_t Lock::write(const void *buffer, const ssize_t buffsize) const {
    lseek(this->fd, 0, SEEK_END);
    return ::write(this->fd, buffer, buffsize);
}

Lock::~Lock() {
    close(this->fd);
}
