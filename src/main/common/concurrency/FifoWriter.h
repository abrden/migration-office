#ifndef FIFOESCRITURA_H_
#define FIFOESCRITURA_H_

#include "Fifo.h"

class FifoWriter : public Fifo {

	public:
		FifoWriter(const std::string nombre);
		void fifo_open();
		ssize_t fifo_write(const void* buffer,const ssize_t buffsize) const;
		~FifoWriter();

};

#endif /* FIFOESCRITURA_H_ */
