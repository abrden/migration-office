#include "SharedLock.h"

#include "unistd.h"

SharedLock::SharedLock(const std::string &name) : Lock(name) {
    this->fl.l_type = F_RDLCK;
    this->fl.l_whence = SEEK_SET;
    this->fl.l_start = 0;
    this->fl.l_len = 0;
    this->fd = open(this->name.c_str(), O_CREAT | O_RDONLY, 0777);
}

int SharedLock::lock() {
    this->fl.l_type = F_RDLCK;
    return fcntl(this->fd, F_SETLKW, &(this->fl));
}
