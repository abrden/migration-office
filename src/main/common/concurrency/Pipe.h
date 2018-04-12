#ifndef MIGRATION_OFFICE_PIPE_H
#define MIGRATION_OFFICE_PIPE_H

#include <unistd.h>
#include <fcntl.h>

class Pipe {

	protected:
		int descriptors[2];
		static const int READ = 0;
		static const int WRITE = 1;

	public:
		Pipe();
		virtual ~Pipe();

};

#endif /* MIGRATION_OFFICE_PIPE_H */
