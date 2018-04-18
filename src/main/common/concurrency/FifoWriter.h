#ifndef MIGRATION_OFFICE_FIFOWRITER_H
#define MIGRATION_OFFICE_FIFOWRITER_H

#include "Fifo.h"

class FifoWriter : public Fifo {

    public:
        explicit FifoWriter(const std::string name);
        void fifo_open() override;
        ssize_t fifo_write(const void* buffer, const ssize_t buffsize) const;

};

#endif /* MIGRATION_OFFICE_FIFOWRITER_H */
