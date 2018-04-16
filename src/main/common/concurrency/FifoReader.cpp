#include "FifoReader.h"

FifoReader::FifoReader(const std::string name) : Fifo(name) {
	fifo_open();
}

void FifoReader::fifo_open() {
	fd = open(name.c_str(), O_RDONLY);
}

ssize_t FifoReader::fifo_read(void* buffer,const ssize_t buffsize) const {
	return read(fd, buffer, buffsize);
}
