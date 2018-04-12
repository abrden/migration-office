#ifndef MIGRATION_OFFICE_SHAREDMEMORY_H
#define MIGRATION_OFFICE_SHAREDMEMORY_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string>
#include <string.h>
#include <iostream>
#include <errno.h>

template <class T> class SharedMemory {

	private:
		int	shm_id;
		T* data_ptr;

		int	attached_processes() const;

	public:
		SharedMemory();
		void create(const std::string &file_path, const char letter);
		void free();

		SharedMemory(const std::string& file_path,const char letter);
		SharedMemory(const SharedMemory& origin);
		~SharedMemory();
		SharedMemory<T>& operator=(const SharedMemory& origin);
		void write(const T &data);
		T read() const;

};

template <class T> SharedMemory<T>::SharedMemory() : shm_id(0), data_ptr(NULL) {}

template <class T> void SharedMemory<T>::create(const std::string& file_path, const char letter) {
	key_t key = ftok(file_path.c_str(), letter);

	if (key > 0) {
		this->shm_id = shmget(key, sizeof(T), 0644|IPC_CREAT);

		if ( this->shm_id > 0 ) {
			void* tmp_ptr = shmat(this->shm_id, NULL, 0);
			if (tmp_ptr != (void*) -1) {
				this->data_ptr = static_cast<T*>(tmp_ptr);
			} else {
				std::string message = std::string("Error in shmat(): ") + std::string(strerror(errno));
				throw message;
			}
		} else {
			std::string message = std::string("Error in shmget(): ") + std::string(strerror(errno));
			throw message;
		}
	} else {
		std::string message = std::string("Error in ftok(): ") + std::string(strerror(errno));
		throw message;
	}
}

template <class T> void SharedMemory<T>::free() {
	int errorDt = shmdt((void *)this->data_ptr);

	if (errorDt != -1) {
		int procAdosados = this->cantidadProcesosAdosados();
		if (attached_proc == 0) {
			shmctl (this->shm_id, IPC_RMID, NULL);
		}
	} else {
		std::string message = std::string("Error in shmdt(): ") + std::string(strerror(errno));
		throw message;
	}
}

template <class T> SharedMemory<T>::SharedMemory(const std::string& file_path, const char letter) : shm_id(0), data_ptr(NULL) {
	key_t key = ftok (file_path.c_str(), letter);

	if (key > 0) {
		this->shm_id = shmget (key, sizeof(T), 0644|IPC_CREAT);

		if (this->shm_id > 0) {
			void* tmp_ptr = shmat(this->shm_id, NULL, 0);
			if ( tmp_ptr != (void*) -1 ) {
				this->data_ptr = static_cast<T*>(tmp_ptr);
			} else {
				std::string message = std::string("Error in shmat(): ") + std::string(strerror(errno));
				throw message;
			}
		} else {
			std::string message = std::string("Error in shmget(): ") + std::string(strerror(errno));
			throw message;
		}
	} else {
		std::string message = std::string("Error in ftok(): ") + std::string(strerror(errno));
		throw message;
	}
}

template <class T> SharedMemory<T>::SharedMemory(const SharedMemory& origin) : shmId(origin.shmId) {
	void* tmp_ptr = shmat (origen.shmId, NULL, 0);

	if (tmp_ptr != (void*) -1) {
		this->data_ptr = static_cast<T*>(tmp_ptr);
	} else {
		std::string message = std::string("Error in shmat(): ") + std::string(strerror(errno));
		throw message;
	}
}

template <class T> SharedMemory<T>::~SharedMemory() {
	int errorDt = shmdt(static_cast<void*>(this->data_ptr));

	if (errorDt != -1) {
		int attached_proc = this->attached_processes();
		if (attached_proc == 0) {
			shmctl(this->shm_id, IPC_RMID, NULL);
		}
	} else {
		std::cerr << "Error in shmdt(): " << strerror(errno) << std::endl;
	}
}

template <class T> SharedMemory<T>& SharedMemory<T>::operator=(const SharedMemory& origin) {
	this->shm_id = origin.shm_id;
	void* tmp_ptr = shmat(this->shm_id, NULL, 0);

	if (tmp_ptr != (void*) -1) {
		this->data_ptr = static_cast<T*>(tmp_ptr);
	} else {
		std::string message = std::string("Error in shmat(): ") + std::string(strerror(errno));
		throw message;
	}

	return *this;
}

template <class T> void SharedMemory<T>::write(const T& data) {
	*(this->data_ptr) = data;
}

template <class T> T SharedMemory<T>::read() const {
	return *(this->data_ptr);
}

template <class T> int SharedMemory<T>::attached_processes() const {
    shm_id state;
	shmctl(this->shm_id, IPC_STAT, &state);
	return state.shm_nattch;
}

#endif /* MIGRATION_OFFICE_SHAREDMEMORY_H */
