#include "FifoWriter.h"

FifoWriter::FifoWriter(const std::string nombre) : Fifo(nombre) {
}

FifoWriter::~FifoWriter() {
}

void FifoWriter::fifo_open() {
	fd = open(name.c_str(), O_WRONLY);
}

ssize_t FifoWriter::fifo_write(const void* buffer,const ssize_t buffsize) const {
	return write(fd,buffer, buffsize);
}
