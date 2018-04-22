#ifndef MIGRATION_OFFICE_MIGRATIONOFFICE_H
#define MIGRATION_OFFICE_MIGRATIONOFFICE_H

#include <list>
#include <string>
#include <vector>

#include "Logger.h"
#include "SIGINTHandler.h"

class MigrationOffice {

    private:
        const int booths_number, stampers_number;
        const std::string people_file, alerts_file, fugitives_file;
        const bool debug;
        const std::string log_file;
        SIGINTHandler sigint_handler;
        std::list<pid_t> children_pids;

        Logger logger;

        void wait_children();
        void fork_new_process(std::vector<char*>& argvs);

    public:
        MigrationOffice(const int booths_number, const int stampers_number,
                        const std::string people_file, const std::string alerts_file,
                        const std::string fugitives_file, const bool debug, const std::string log_file);
        void start();
        void open_ministry_of_security();
        void open_booths();
        void fork_spawner();
        void open_statistics();
        ~MigrationOffice();

};


#endif //MIGRATION_OFFICE_MIGRATIONOFFICE_H
