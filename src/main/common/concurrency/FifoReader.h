#ifndef MIGRATION_OFFICE_FIFOREADER_H
#define MIGRATION_OFFICE_FIFOREADER_H

#include "Fifo.h"

class FifoReader : public Fifo {

    public:
        explicit FifoReader(const std::string name);
        void fifo_open() override;
        ssize_t fifo_read(void *buffer, const ssize_t buffsize) const;
        ~FifoReader() override;

};

#endif /* MIGRATION_OFFICE_FIFOREADER_H */
