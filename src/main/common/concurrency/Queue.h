#ifndef COLA_H_
#define COLA_H_

#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <string>

template<class T>
class Queue {
        
        private:
            key_t clave;
            int id;
    
        public:
            Queue(const std::string &archivo, const char letra);
            ~Queue();
            int write(const T &dato) const;
            int read(const int tipo, T *buffer) const;
            int destroy() const;
            
};

template<class T>
Queue<T>::Queue(const std::string &archivo, const char letra) {
    this->clave = ftok(archivo.c_str(), letra);
    if (this->clave==-1)
        perror("Error en ftok");

    this->id = msgget(this->clave, 0777 | IPC_CREAT);
    if (this->id==-1)
        perror("Error en msgget");
}

template<class T>
Queue<T>::~Queue() {
}

template<class T>
int Queue<T>::destroy() const {
    int resultado = msgctl(this->id, IPC_RMID, NULL);
    return resultado;
}

template<class T>
int Queue<T>::write(const T &dato) const {
    int resultado = msgsnd(this->id, static_cast<const void *>(&dato), sizeof(T) - sizeof(long), 0);
    return resultado;
}

template<class T>
int Queue<T>::read(const int tipo, T *buffer) const {
    int resultado = msgrcv(this->id, static_cast<void *>(buffer), sizeof(T) - sizeof(long), tipo, 0);
    return resultado;
}

#endif /* COLA_H_ */
