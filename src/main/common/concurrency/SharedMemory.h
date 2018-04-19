#ifndef MIGRATION_OFFICE_SHAREDMEMORY_H
#define MIGRATION_OFFICE_SHAREDMEMORY_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string>
#include <cstring>
#include <iostream>
#include <cerrno>

template<class T>
class SharedMemory {

    private:
        int shm_id;
        T* data_ptr;

        int attached_processes() const;

    public:
        SharedMemory();
        SharedMemory(const std::string& file_path, const char letter);
        SharedMemory(const SharedMemory& origin);
        void create(const std::string& file_path, const char letter);
        void free();
        SharedMemory<T>& operator=(const SharedMemory& origin);
        void write(const T& data);
        T read() const;
        ~SharedMemory();

};

template<class T>
SharedMemory<T>::SharedMemory() : shm_id(0), data_ptr(nullptr) {}

template<class T>
SharedMemory<T>::SharedMemory(const std::string& file_path, const char letter) : shm_id(0), data_ptr(nullptr) {
    key_t key = ftok(file_path.c_str(), letter);

    if (key > 0) {
        this->shm_id = shmget(key, sizeof(T), 0644 | IPC_CREAT);

        if (this->shm_id > 0) {
            void* tmp_ptr = shmat(this->shm_id, nullptr, 0);
            if (tmp_ptr != (void*) -1) {
                this->data_ptr = static_cast<T*>(tmp_ptr);
            } else {
                std::string message = std::string("Error in shmat(): ") + std::string(strerror(errno));
                throw std::system_error(errno, std::system_category(), message);
            }
        } else {
            std::string message = std::string("Error in shmget(): ") + std::string(strerror(errno));
            throw std::system_error(errno, std::system_category(), message);
        }
    } else {
        std::string message = std::string("Error in ftok(): ") + std::string(strerror(errno));
        throw std::system_error(errno, std::system_category(), message);
    }
}

template<class T>
SharedMemory<T>::SharedMemory(const SharedMemory& origin) : shm_id(origin.shm_id) {
    void* tmp_ptr = shmat(origin.shm_id, nullptr, 0);

    if (tmp_ptr != (void*) -1) {
        this->data_ptr = static_cast<T*>(tmp_ptr);
    } else {
        std::string message = std::string("Error in shmat(): ") + std::string(strerror(errno));
        throw std::system_error(errno, std::system_category(), message);
    }
}

template<class T>
void SharedMemory<T>::create(const std::string& file_path, const char letter) {
    key_t key = ftok(file_path.c_str(), letter);

    if (key > 0) {
        this->shm_id = shmget(key, sizeof(T), 0644 | IPC_CREAT);

        if (this->shm_id > 0) {
            void* tmp_ptr = shmat(this->shm_id, nullptr, 0);
            if (tmp_ptr != (void *) -1) {
                this->data_ptr = static_cast<T*>(tmp_ptr);
            } else {
                std::string message = std::string("Error in shmat(): ") + std::string(strerror(errno));
                throw std::system_error(errno, std::system_category(), message);
            }
        } else {
            std::string message = std::string("Error in shmget(): ") + std::string(strerror(errno));
            throw std::system_error(errno, std::system_category(), message);
        }
    } else {
        std::string message = std::string("Error in ftok(): ") + std::string(strerror(errno));
        throw std::system_error(errno, std::system_category(), message);
    }
}

template<class T>
void SharedMemory<T>::free() {
    int errorDt = shmdt((void*) this->data_ptr);

    if (errorDt != -1) {
        int attached_proc = this->attached_processes();
        if (attached_proc == 0) {
            shmctl(this->shm_id, IPC_RMID, nullptr);
        }
    } else {
        std::string message = std::string("Error in shmdt(): ") + std::string(strerror(errno));
        throw std::system_error(errno, std::system_category(), message);
    }
}

template<class T>
SharedMemory<T> &SharedMemory<T>::operator=(const SharedMemory &origin) {
    this->shm_id = origin.shm_id;
    void *tmp_ptr = shmat(this->shm_id, nullptr, 0);

    if (tmp_ptr != (void*) -1) {
        this->data_ptr = static_cast<T*>(tmp_ptr);
    } else {
        std::string message = std::string("Error in shmat(): ") + std::string(strerror(errno));
        throw std::system_error(errno, std::system_category(), message);
    }

    return *this;
}

template<class T>
void SharedMemory<T>::write(const T &data) {
    *(this->data_ptr) = data;
}

template<class T>
T SharedMemory<T>::read() const {
    return *(this->data_ptr);
}

template<class T>
int SharedMemory<T>::attached_processes() const {
    shmid_ds state;
    shmctl(this->shm_id, IPC_STAT, &state);
    return state.shm_nattch;
}

template<class T>
SharedMemory<T>::~SharedMemory() {
    int errorDt = shmdt(static_cast<void *>(this->data_ptr));

    if (errorDt != -1) {
        int attached_proc = this->attached_processes();
        if (attached_proc == 0) {
            shmctl(this->shm_id, IPC_RMID, nullptr);
        }
    } else {
        std::cerr << "Error in shmdt(): " << strerror(errno) << std::endl;
    }
}

#endif /* MIGRATION_OFFICE_SHAREDMEMORY_H */
