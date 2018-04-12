#ifndef MIGRATION_OFFICE_FIFOWRITER_H
#define MIGRATION_OFFICE_FIFOWRITER_H

#include "Fifo.h"

class FifoWriter : public Fifo {

	public:
		FifoWriter(const std::string nombre);
		void fifo_open();
		ssize_t fifo_write(const void* buffer,const ssize_t buffsize) const;
		~FifoWriter();

};

#endif /* MIGRATION_OFFICE_FIFOWRITER_H */
