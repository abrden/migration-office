#include "Semaphore.h"

Semaphore::Semaphore(const std::string& file, const char letter, const int initial_value) : initial_value(initial_value) {
    key_t key = ftok(file.c_str(), letter);
    this->id = semget(key, 1, 0666 | IPC_CREAT);

    this->init();
}

Semaphore::~Semaphore() = default;

int Semaphore::init() const {

    union semnum {
        int val;
        struct semid_ds *buf;
        ushort *array;
    };

    semnum init;
    init.val = this->initial_value;
    int resultado = semctl(this->id, 0, SETVAL, init);
    return resultado;
}

int Semaphore::p() const {

    struct sembuf op;

    op.sem_num = 0;
    op.sem_op = -1;
    op.sem_flg = SEM_UNDO;

    int resultado = semop(this->id, &op, 1);
    return resultado;
}

int Semaphore::v() const {

    struct sembuf op;

    op.sem_num = 0;
    op.sem_op = 1;
    op.sem_flg = SEM_UNDO;

    int resultado = semop(this->id, &op, 1);
    return resultado;
}

void Semaphore::destroy() const {
    semctl(id, 0, IPC_RMID);
}
