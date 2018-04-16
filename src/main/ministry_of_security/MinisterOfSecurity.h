#ifndef MIGRATION_OFFICE_MINISTEROFSECURITY_H
#define MIGRATION_OFFICE_MINISTEROFSECURITY_H

#include "WantedPersonAlert.h"
#include "Spawner.h"
#include "FifoWriter.h"
#include "SIGINTHandler.h"

#include <vector>


class MinisterOfSecurity {

    private:
        SIGINTHandler sigint_handler;
        FifoWriter fifo;
        Spawnables alerts;
        std::vector<unsigned int> fugitives;
        const size_t booths_number;

        void send_fugitives();
        void send_alerts();

    public:
        MinisterOfSecurity(const std::string& alerts_file_path,
                           const std::string& fugitives_file_path,
                           const size_t booths_number);
        void open();
        Spawnables& get_alerts();
        ~MinisterOfSecurity();

};


#endif //MIGRATION_OFFICE_MINISTEROFSECURITY_H
