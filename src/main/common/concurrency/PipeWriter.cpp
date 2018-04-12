#include "PipeWriter.h"

PipeWriter::PipeWriter() {
    close(descriptors[READ]);
    fd = descriptors[WRITE];
}

ssize_t PipeWriter::pipe_write(const void* data, int data_size) {
    return write (fd, data, data_size);
}

PipeWriter::~PipeWriter() {
    close(fd);
}