#include "ExclusiveLock.h"

#include "unistd.h"

ExclusiveLock::ExclusiveLock(const std::string &name) : Lock(name) {
    this->fl.l_type = F_WRLCK;
    this->fl.l_whence = SEEK_SET;
    this->fl.l_start = 0;
    this->fl.l_len = 0;
    this->fd = open(this->name.c_str(), O_CREAT | O_WRONLY, 0777);
}

int ExclusiveLock::lock() {
    this->fl.l_type = F_WRLCK;
    return fcntl(this->fd, F_SETLKW, &(this->fl));
}
