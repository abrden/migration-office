#include <cstring>
#include <system_error>
#include <iostream>
#include <unistd.h>
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

    int counter = semctl(this->id, 0, GETVAL, 0);
    std::cout << "============ SMPH CONSTRUCTOR() VALUE: " << counter << std::endl;
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

    int counter = semctl(this->id, 0, GETVAL, 0);
    std::cout << "============ SMPH INIT() VALUE: " << counter << std::endl;

    return ans;
}

int Semaphore::p() const {
    struct sembuf op;
    op.sem_num = 0;
    op.sem_op = -1;
    op.sem_flg = SEM_UNDO;

    int counter = semctl(this->id, 0, GETVAL, 0);
    std::cout << "============ SMPH P() VALUE: " << counter << std::endl;

    if (counter < 0) {
        std::string message = std::string("Error in Semaphore semctl(-1): ") + std::string(strerror(errno));
        throw std::system_error(errno, std::system_category(), message);
    }

    int ans = semop(this->id, &op, 1);
    if (ans < 0) {
        std::string message = std::string("Error in Semaphore semop(-1): ") + std::string(strerror(errno));
        throw std::system_error(errno, std::system_category(), message);
    }

    counter = semctl(this->id, 0, GETVAL, 0);
    std::cout << "============ SMPH AFTER P() VALUE: " << counter << std::endl;

    return ans;
}

int Semaphore::v() const {
    struct sembuf op;
    op.sem_num = 0;
    op.sem_op = 1;
    op.sem_flg = SEM_UNDO;

    int counter = semctl(this->id, 0, GETVAL, 0);
    std::cout << "============ SMPH V() VALUE: " << counter << std::endl;

    if (counter < 0) {
        std::string message = std::string("Error in Semaphore semctl(-1): ") + std::string(strerror(errno));
        throw std::system_error(errno, std::system_category(), message);
    }

    int ans = semop(this->id, &op, 1);
    if (ans < 0) {
        std::string message = std::string("Error in Semaphore semop(1): ") + std::string(strerror(errno));
        throw std::system_error(errno, std::system_category(), message);
    }

    counter = semctl(this->id, 0, GETVAL, 0);
    std::cout << "============ SMPH AFTER V() VALUE: " << counter << std::endl;
    return ans;
}

int Semaphore::w() const {
    struct sembuf op;
    op.sem_num = 0;
    op.sem_op = 0;
    op.sem_flg = SEM_UNDO;

    int counter = semctl(this->id, 0, GETVAL, 0);
    std::cout << "============ SMPH W() VALUE: " << counter << std::endl;

    int ans = semop(this->id, &op, 1);
    if (ans < 0) {
        std::string message = std::string("Error in Semaphore semop(0): ") + std::string(strerror(errno));
        throw std::system_error(errno, std::system_category(), message);
    }

    counter = semctl(this->id, 0, GETVAL, 0);
    std::cout << "============ SMPH AFTER W() VALUE: " << counter << std::endl;
    return ans;
}

int Semaphore::destroy() const {
    int counter = semctl(this->id, 0, GETVAL, 0);
    std::cout << "============ SMPH DESTROY() VALUE: " << counter << std::endl;
    return semctl(id, 0, IPC_RMID);
}