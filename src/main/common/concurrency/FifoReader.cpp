#include <system_error>
#include "FifoReader.h"

FifoReader::FifoReader(const std::string name) : Fifo(name) {
	fifo_open();
}

void FifoReader::fifo_open() {
	fd = open(name.c_str(), O_RDONLY);
    if (fd == -1) {
        throw std::system_error(errno, std::system_category(), "Error in open: could not open Fifo file in read mode");
    }
}

ssize_t FifoReader::fifo_read(void* buffer,const ssize_t buffsize) const {
	return read(fd, buffer, buffsize);
}
