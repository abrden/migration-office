#include <cstring>
#include <system_error>
#include <iostream>
#include "Semaphore.h"

Semaphore::Semaphore(const std::string& file, const char letter) {
    key_t key = ftok(file.c_str(), letter);
    if (key < 0) {
        std::string message = std::string("Error in Semaphore ftok(): ") + std::string(strerror(errno));
        throw std::system_error(errno, std::system_category(), message);
    }

    id = semget(key, 1, 0666 | IPC_CREAT);
    if (id < 0) {
        std::string message = std::string("Error in Semaphore semget(): ") + std::string(strerror(errno));
        throw std::system_error(errno, std::system_category(), message);
    }
}

int Semaphore::init(const int initial_value) const {
    union semnum {
        int val;
        struct semid_ds *buf;
        ushort *array;
    };
    semnum init;
    init.val = initial_value;

    int ans = semctl(this->id, 0, SETVAL, init);
    if (ans < 0) {
        std::string message = std::string("Error in Semaphore semctl(): ") + std::string(strerror(errno));
        throw std::system_error(errno, std::system_category(), message);
    }

    return ans;
}

int Semaphore::p() const {
    struct sembuf op;
    op.sem_num = 0;
    op.sem_op = -1;
    op.sem_flg = 0;

    int ans = semop(this->id, &op, 1);
    if (ans < 0) {
        std::string message = std::string("Error in Semaphore semop(-1): ") + std::string(strerror(errno));
        throw std::system_error(errno, std::system_category(), message);
    }

    return ans;
}

int Semaphore::v() const {
    struct sembuf op;
    op.sem_num = 0;
    op.sem_op = 1;
    op.sem_flg = 0;

    int ans = semop(this->id, &op, 1);
    if (ans < 0) {
        std::string message = std::string("Error in Semaphore semop(1): ") + std::string(strerror(errno));
        throw std::system_error(errno, std::system_category(), message);
    }

    return ans;
}

int Semaphore::w() const {
    struct sembuf op;
    op.sem_num = 0;
    op.sem_op = 0;
    op.sem_flg = 0;

    int ans = semop(this->id, &op, 1);
    if (ans < 0) {
        std::string message = std::string("Error in Semaphore semop(0): ") + std::string(strerror(errno));
        throw std::system_error(errno, std::system_category(), message);
    }
    return ans;
}

int Semaphore::destroy() const {
    return semctl(id, 0, IPC_RMID);
}