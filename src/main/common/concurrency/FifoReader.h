#ifndef FIFOLECTURA_H_
#define FIFOLECTURA_H_

#include "Fifo.h"

class FifoReader : public Fifo {

	public:
		FifoReader(const std::string name);
		void fifo_open();
		ssize_t fifo_read(void* buffer, const ssize_t buffsize) const;
		~FifoReader();

};

#endif /* FIFOLECTURA_H_ */
