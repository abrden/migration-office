#include "AlertsSharedMemory.h"
#include "AlertData.h"

#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstring>
#include <iostream>
#include <system_error>

AlertsSharedMemory::AlertsSharedMemory(const std::string& file_path, const char letter, const size_t size) : shm_id(0), alerts(nullptr) {
    key_t key = ftok(file_path.c_str(), letter);

    if (key > 0) {
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

std::string AlertsSharedMemory::serialize_alert_data(AlertData data) {
    std::string s;

    char* id_arr = (char*)&data.id;
    for (unsigned int i = 0; i < sizeof(data.id); ++i)
        s.push_back(id_arr[i]);

    char* size_arr = (char*)&data.serialized_alert_size;
    for (unsigned int i = 0; i < sizeof(data.serialized_alert_size); ++i)
        s.push_back(size_arr[i]);

    for (size_t i = 0; i < data.serialized_alert_size; ++i)
        s.push_back(data.serialized_alert[i]);

    return s;
}

void AlertsSharedMemory::write(size_t pos, const AlertData& alert) {
    std::string serialized_alert = serialize_alert_data(alert);
    serialized_alert.copy(alerts[pos], SERIALIZED_ALERT_SIZE, 0);
}

AlertData AlertsSharedMemory::read(size_t pos) const {
    std::string serialized_alert(alerts[pos], SERIALIZED_ALERT_SIZE);

    size_t id, size;
    serialized_alert.copy((char*)&id, sizeof(size_t), 0);
    serialized_alert.copy((char*)&size, sizeof(size_t), sizeof(size_t));
    std::string alert_str = serialized_alert.substr(2 * sizeof(size_t), size);

    AlertData alert;
    alert.id = id;
    alert.serialized_alert_size = size;
    alert_str.copy(alert.serialized_alert, size, 0);

    return alert;
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