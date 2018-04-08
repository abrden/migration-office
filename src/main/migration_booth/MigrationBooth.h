#ifndef MIGRATION_OFFICE_MIGRATIONBOOTH_H
#define MIGRATION_OFFICE_MIGRATIONBOOTH_H

#include <string>

class MigrationBooth {

    private:
        const std::string people_file, alerts_file, fugitives_file;
        const bool debug;
        const std::string log_file;

    public:
        MigrationBooth(const std::string people_file, const std::string alerts_file, const std::string fugitives_file,
                       const bool debug, const std::string log_file);

};


#endif //MIGRATION_OFFICE_MIGRATIONBOOTH_H
