#include "PipeReader.h"

PipeReader::PipeReader() {
    close(descriptors[WRITE]);
    fd = descriptors[READ];
}

ssize_t PipeReader::pipe_read(void* buffer, int buffer_size) {
    return read(fd, buffer, buffer_size);
}

PipeReader::~PipeReader() {
    close(fd);
}