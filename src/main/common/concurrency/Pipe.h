#ifndef PIPE_H_
#define PIPE_H_

#include <unistd.h>
#include <fcntl.h>

class Pipe {

	protected:
		int descriptors[2];
		static const int LECTURA = 0;
		static const int ESCRITURA = 1;

	public:
		Pipe();
		virtual ~Pipe();

};

#endif /* PIPE_H_ */
