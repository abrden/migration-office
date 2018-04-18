#ifndef MIGRATION_OFFICE_MINISTEROFSECURITY_H
#define MIGRATION_OFFICE_MINISTEROFSECURITY_H

#include "WantedPersonAlert.h"
#include "Spawner.h"
#include "FifoWriter.h"
#include "FifoReader.h"
#include "SIGINTHandler.h"

#include <vector>

class MinisterOfSecurity {

    private:
        SIGINTHandler sigint_handler;
        FifoWriter fugitives_fifo;
        FifoReader booths_fifo;
        Spawnables alerts;
        std::vector<unsigned int> fugitives;
        const size_t booths_number;

        void send_fugitives();
        void send_alerts();
        void receive_confirmations();

    public:
        MinisterOfSecurity(const std::string& alerts_file_path,
                           const std::string& fugitives_file_path,
                           const size_t booths_number);
        void open();
        ~MinisterOfSecurity();

};


#endif //MIGRATION_OFFICE_MINISTEROFSECURITY_H
