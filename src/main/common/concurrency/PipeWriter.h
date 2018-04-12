#ifndef MIGRATION_OFFICE_PIPEWRITER_H
#define MIGRATION_OFFICE_PIPEWRITER_H

#include "Pipe.h"

class PipeWriter : public Pipe {

    private:
        int fd;

    public:
        PipeWriter();
        ssize_t pipe_write(const void* data, int data_size);
        ~PipeWriter();

};


#endif //MIGRATION_OFFICE_PIPEWRITER_H
