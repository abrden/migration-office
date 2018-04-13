#ifndef MIGRATION_OFFICE_FIFOWRITER_H
#define MIGRATION_OFFICE_FIFOWRITER_H

#include "Fifo.h"

class FifoWriter : public Fifo {

    public:
        explicit FifoWriter(const std::string nombre);
        void fifo_open() override;
        ssize_t fifo_write(const void* buffer, const ssize_t buffsize) const;
        ~FifoWriter() override;

};

#endif /* MIGRATION_OFFICE_FIFOWRITER_H */
