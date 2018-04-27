#ifndef MIGRATION_OFFICE_MINISTEROFSECURITY_H
#define MIGRATION_OFFICE_MINISTEROFSECURITY_H

#include "Spawner.h"
#include "FifoWriter.h"
#include "FifoReader.h"
#include "Logger.h"
#include "AlertSpawner.h"

#include <vector>

class MinisterOfSecurity {

    private:
        Logger logger;

        FifoWriter fugitives_fifo;
        FifoReader booths_fifo;

        std::vector<unsigned int> fugitives;
        const size_t booths_number;

        void send_fugitives();

        AlertSpawner alerts_spawner;
        void send_alerts();
        void receive_confirmations();

    public:
        MinisterOfSecurity(const std::string& alerts_file_path,
                           const std::string& fugitives_file_path,
                           const size_t booths_number,
                           const std::vector<pid_t>& booths_ids,
                           const bool debug,
                           const std::string& log_file_path);
        void open();
        ~MinisterOfSecurity();

};


#endif //MIGRATION_OFFICE_MINISTEROFSECURITY_H
