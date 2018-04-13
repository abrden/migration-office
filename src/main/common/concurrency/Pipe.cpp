#include "Pipe.h"

Pipe::Pipe() {
	pipe(this->descriptors);
}

Pipe::~Pipe() = default;
