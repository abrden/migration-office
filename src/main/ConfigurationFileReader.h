#ifndef MIGRATION_OFFICE_FILE_H
#define MIGRATION_OFFICE_FILE_H


#include "Spawnables.h"

class ConfigurationFileReader {

    public:
        void load_alerts(const std::string& file_path, Spawnables& alerts);

};


#endif //MIGRATION_OFFICE_FILE_H
