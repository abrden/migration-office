#include "Logger.h"

#include <unistd.h>
#include <iostream>
#include <cstring>
#include <system_error>

const static std::string LOGGER_LOCK_FILE = "/tmp/logger_lock";

Logger::Logger(const bool debug, const std::string& file) : file(file), lock(LOGGER_LOCK_FILE) {
    if (!debug) this->file = "/dev/null";
}

const std::string Logger::build_log_message() {
    std::ostringstream tmp;
    tmp <<  "[" << getpid() << "] " << oss.str() << std::endl;
    return tmp.str();
}

Logger& Logger::operator()(const std::string& transmitter) {
    oss << transmitter << ": ";
    return *this;
}

Logger& Logger::operator<<(io_manip_ptr_t f) {
    if (f == (io_manip_ptr_t)&std::endl) {

        const std::string message = build_log_message();

        // FIXME Delete me when you feel ready
        std::cout << message;
        //

        lock.lock();
        int fd = open(file.c_str(), O_WRONLY | O_CREAT, 0666);
        lseek(fd, 0, SEEK_END);

        ssize_t bytes_written = write(fd, message.c_str(), message.size());
        if ((unsigned long) bytes_written != message.size()) {
            close(fd);
            lock.unlock();
            oss.str("");

            std::string message = std::string("Error in write: could not write Logger file: ") + std::string(strerror(errno));
            throw std::system_error(errno, std::system_category(), message);
        }

        close(fd);
        lock.unlock();

        oss.str("");
    }
    return *this;
}