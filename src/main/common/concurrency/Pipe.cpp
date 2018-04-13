#include <system_error>
#include "Pipe.h"

Pipe::Pipe() {
	if (pipe(this->descriptors) == -1) {
	    throw std::system_error(errno, std::generic_category());
	}
}

Pipe::~Pipe() = default;
