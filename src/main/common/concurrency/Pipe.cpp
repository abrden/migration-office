#include "Pipe.h"

Pipe::Pipe() {
	pipe(this->descriptors);
	/*fcntl ( this->descriptors[0],F_SETFL,O_NONBLOCK );
	fcntl ( this->descriptors[1],F_SETFL,O_NONBLOCK );*/
}

Pipe::~Pipe() {}
