#ifndef MIGRATION_OFFICE_PIPEREADER_H
#define MIGRATION_OFFICE_PIPEREADER_H

#include "Pipe.h"

class PipeReader : public Pipe {

    private:
        int fd;

    public:
        PipeReader();
        ssize_t pipe_read(void* buffer, int buffer_size);
        ~PipeReader() override;

};


#endif /* MIGRATION_OFFICE_PIPEREADER_H */
