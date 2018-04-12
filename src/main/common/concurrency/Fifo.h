#ifndef FIFO_H_
#define FIFO_H_

#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

class Fifo {

	public:
		Fifo(const std::string name);
		virtual void fifo_open() = 0;
		void fifo_close();
		void fifo_unlink() const;
		virtual ~Fifo();

	protected:
		std::string name;
		int fd;

};

#endif /* FIFO_H_ */
