#include <system_error>
#include "FifoWriter.h"

FifoWriter::FifoWriter(const std::string name) : Fifo(name) {
	fifo_open();
}

void FifoWriter::fifo_open() {
	fd = open(name.c_str(), O_WRONLY);
	if (fd == -1) {
	    throw std::system_error(errno, std::system_category(), "Error in open: could not open Fifo file in write mode.");
	}
}

ssize_t FifoWriter::fifo_write(const void* buffer,const ssize_t buffsize) const {
	return write(fd,buffer, buffsize);
}
