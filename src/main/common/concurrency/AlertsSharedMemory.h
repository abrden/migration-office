#ifndef MIGRATION_OFFICE_ALERTSSHAREDMEMORY_H
#define MIGRATION_OFFICE_ALERTSSHAREDMEMORY_H

#include "AlertData.h"

#include <sys/shm.h>
#include <string>

class AlertsSharedMemory {

    private:
        int shm_id;
        SerializedAlert* alerts;

        shmatt_t attached_processes() const;

    public:
        AlertsSharedMemory(const std::string& file_path, const char letter, const size_t size);
        void write(size_t pos, const std::string& serialized_alert);
        std::string read(size_t pos) const;
        ~AlertsSharedMemory();

};


#endif //MIGRATION_OFFICE_ALERTSSHAREDMEMORY_H
