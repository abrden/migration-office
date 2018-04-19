#ifndef MIGRATION_OFFICE_POLICE_H
#define MIGRATION_OFFICE_POLICE_H

#include "Resident.h"
#include "Foreigner.h"
#include "FifoReader.h"
#include "FifoWriter.h"
#include "ExclusiveLock.h"

#include <vector>

class Police {

    private:
        FifoReader fugitives_fifo;
        FifoWriter ministry_fifo;
        ExclusiveLock fugitives_fifo_lock;

        std::vector<unsigned int> fugitives;

        size_t arrested_residents;
        size_t deported_foreigners;

        void receive_fugitives();

    public:
        Police();
        bool is_fugitive(Resident* resident);
        bool is_wanted_person(Foreigner* foreigner);
        void report(Resident* resident);
        void report(Foreigner* foreigner);

};


#endif //MIGRATION_OFFICE_POLICE_H
