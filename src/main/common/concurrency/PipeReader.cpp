#include "PipeReader.h"

PipeReader::PipeReader() {
    close(descriptors[ESCRITURA]);
    fd = descriptors[LECTURA];
}

ssize_t PipeReader::pipe_read(void* buffer, int buffer_size) {
    return read (fd, buffer, buffer_size);
}

PipeReader::~PipeReader() {
    close(fd);
}