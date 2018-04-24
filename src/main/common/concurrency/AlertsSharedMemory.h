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
        std::string serialize_alert_data(AlertData data);

    public:
        AlertsSharedMemory(const std::string& file_path, const char letter, const size_t size);
        void write(size_t pos, const AlertData& alert);
        AlertData read(size_t pos) const;
        ~AlertsSharedMemory();

};


#endif //MIGRATION_OFFICE_ALERTSSHAREDMEMORY_H
