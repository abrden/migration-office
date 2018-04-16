#include <system_error>
#include "Fifo.h"

Fifo::Fifo(const std::string name) : name(name), fd(-1) {
	if (mknod(static_cast<const char*>(name.c_str()), S_IFIFO|0666, 0) == -1) {
	    // FIXME throwing error when file already exists
//	    throw std::system_error(errno, std::system_category(), "Error in mknod: could not create file.");
	};
}

void Fifo::fifo_close() {
	close(fd);
	fd = -1;
}

void Fifo::fifo_unlink() const {
	unlink(name.c_str());
}

Fifo::~Fifo() {
    fifo_close();
    fifo_unlink();
}