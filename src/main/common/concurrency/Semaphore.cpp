#include <cstring>
#include <system_error>
#include "Semaphore.h"

Semaphore::Semaphore(const std::string& file, const char letter, const int initial_value) : initial_value(initial_value) {
    key_t key = ftok(file.c_str(), letter);
    if (key < 0) {
        std::string message = std::string("Error in ftok(): ") + std::string(strerror(errno));
        throw std::system_error(errno, std::system_category(), message);
    }

    id = semget(key, 1, 0666 | IPC_CREAT);
    if (id < 0) {
        std::string message = std::string("Error in semget(): ") + std::string(strerror(errno));
        throw std::system_error(errno, std::system_category(), message);
    }
}

int Semaphore::init() const {
    union semnum {
        int val;
        struct semid_ds *buf;
        ushort *array;
    };
    semnum init;
    init.val = this->initial_value;

    int ans = semctl(this->id, 0, SETVAL, init);
    if (ans < 0) {
        std::string message = std::string("Error in semctl(): ") + std::string(strerror(errno));
        throw std::system_error(errno, std::system_category(), message);
    }

    return ans;
}

int Semaphore::p() const {
    struct sembuf op;
    op.sem_num = 0;
    op.sem_op = -1;
    op.sem_flg = SEM_UNDO;

    int ans = semop(this->id, &op, 1);
    if (ans < 0) {
        std::string message = std::string("Error in semop(): ") + std::string(strerror(errno));
        throw std::system_error(errno, std::system_category(), message);
    }

    return ans;
}

int Semaphore::v() const {
    struct sembuf op;
    op.sem_num = 0;
    op.sem_op = 1;
    op.sem_flg = SEM_UNDO;

    int ans = semop(this->id, &op, 1);
    if (ans < 0) {
        std::string message = std::string("Error in semop(): ") + std::string(strerror(errno));
        throw std::system_error(errno, std::system_category(), message);
    }

    return ans;
}

Semaphore::~Semaphore() {
    semctl(id, 0, IPC_RMID);
};