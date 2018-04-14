#include "ExclusiveLock.h"

#include "unistd.h"
#include <system_error>

ExclusiveLock::ExclusiveLock(const std::string& name) : Lock(name) {
    fl.l_type = F_WRLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = 0;
    fl.l_len = 0;
    fd = open(this->name.c_str(), O_CREAT | O_WRONLY, 0777);
    if (fd == -1) {
        throw std::system_error(errno, std::generic_category(), "Error when trying to open file.");
    }
}

int ExclusiveLock::lock() {
    fl.l_type = F_WRLCK;
    int lock_fd = fcntl(fd, F_SETLKW, &(fl));
    if (lock_fd == -1) {
        throw std::system_error(errno, std::generic_category(), "Error when trying to lock file.");
    }
    return lock_fd;
}
