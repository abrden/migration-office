#include "AlertsSharedMemory.h"

#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstring>
#include <iostream>

AlertsSharedMemory::AlertsSharedMemory(const std::string& file_path, const char letter, const size_t size) : shm_id(0), alerts(nullptr) {
    key_t key = ftok(file_path.c_str(), letter);

    if (key > 0) {
        std::cout << "Size of data: " << (sizeof(SerializedAlert) * size) << std::endl;
        this->shm_id = shmget(key, sizeof(SerializedAlert) * size, 0644 | IPC_CREAT);

        if (this->shm_id > 0) {
            void* tmp_ptr = shmat(this->shm_id, nullptr, 0);
            if (tmp_ptr != (void*) -1) {
                this->alerts = static_cast<SerializedAlert*>(tmp_ptr);
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

void AlertsSharedMemory::write(size_t pos, const std::string& serialized_alert) {
    serialized_alert.copy(alerts[pos], SERIALIZED_ALERT_SIZE, 0);
}

std::string AlertsSharedMemory::read(size_t pos) const {
    std::string s(alerts[pos], SERIALIZED_ALERT_SIZE);
    return s;
}

shmatt_t AlertsSharedMemory::attached_processes() const {
    shmid_ds state;
    shmctl(this->shm_id, IPC_STAT, &state);
    return state.shm_nattch;
}

AlertsSharedMemory::~AlertsSharedMemory() {
    int errorDt = shmdt(static_cast<void*>(this->alerts));

    if (errorDt != -1) {
        shmatt_t attached_proc = this->attached_processes();
        if (attached_proc == 0) {
            shmctl(this->shm_id, IPC_RMID, nullptr);
        }
    } else {
        std::cerr << "Error in shmdt(): " << strerror(errno) << std::endl;
    }
}