#include "SharedLock.h"

#include "unistd.h"
#include <system_error>

SharedLock::SharedLock(const std::string& name) : Lock(name) {
    fl.l_type = F_RDLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = 0;
    fl.l_len = 0;
    fd = open(name.c_str(), O_CREAT | O_RDONLY, 0777);
    if (fd == -1) {
        throw std::system_error(errno, std::generic_category(), "Error when trying to open file.");
    }
}

int SharedLock::lock() {
    fl.l_type = F_RDLCK;
    int lock_fd = fcntl(fd, F_SETLKW, &(fl));
    if (lock_fd == -1) {
        throw std::system_error(errno, std::generic_category(), "Error when trying to lock file.");
    }
    return lock_fd;
}
