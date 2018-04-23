#ifndef MIGRATION_OFFICE_SharedMemoryArray_H
#define MIGRATION_OFFICE_SharedMemoryArray_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string>
#include <cstring>
#include <iostream>
#include <cerrno>
#include <system_error>

template<class T>
class SharedMemoryArray {

    private:
        int shm_id;
        T* data_ptr;

        shmatt_t attached_processes() const;

    public:
        SharedMemoryArray(const std::string& file_path, const char letter, const size_t size);
        void write(size_t pos, const T& data);
        T* read() const;
        ~SharedMemoryArray();

};

template<class T>
SharedMemoryArray<T>::SharedMemoryArray(const std::string& file_path, const char letter, const size_t size) : shm_id(0), data_ptr(nullptr) {
    key_t key = ftok(file_path.c_str(), letter);

    if (key > 0) {
        std::cout << "Size of data: " << (sizeof(T) * size) << std::endl;
        this->shm_id = shmget(key, sizeof(T) * size, 0644 | IPC_CREAT);

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
void SharedMemoryArray<T>::write(size_t pos, const T &data) {
    this->data_ptr[pos] = data;
}

template<class T>
T* SharedMemoryArray<T>::read() const {
    return this->data_ptr;
}

template<class T>
shmatt_t SharedMemoryArray<T>::attached_processes() const {
    shmid_ds state;
    shmctl(this->shm_id, IPC_STAT, &state);
    return state.shm_nattch;
}

template<class T>
SharedMemoryArray<T>::~SharedMemoryArray() {
    int errorDt = shmdt(static_cast<void*>(this->data_ptr));

    if (errorDt != -1) {
        shmatt_t attached_proc = this->attached_processes();
        if (attached_proc == 0) {
            shmctl(this->shm_id, IPC_RMID, nullptr);
        }
    } else {
        std::cerr << "Error in shmdt(): " << strerror(errno) << std::endl;
    }
}

#endif /* MIGRATION_OFFICE_SharedMemoryArray_H */
