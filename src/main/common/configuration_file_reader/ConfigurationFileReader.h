#ifndef MIGRATION_OFFICE_FILE_H
#define MIGRATION_OFFICE_FILE_H

#include <vector>
#include <list>

#include "Spawnables.h"
#include "Features.h"

class ConfigurationFileReader {

    public:
        static std::vector<std::string> split_line_into_tokens(std::string& line);
        static std::list<std::string> extract_features(std::vector<std::string>& raw_features);
        static void load_persons(const std::string &file_path, Spawnables &persons);
        static void load_fugitives_ids(const std::string& fugitives_file_path, std::vector<unsigned int> &fugitives_ids);
        static void load_alerts(const std::string& file_path, Spawnables& alerts);
        static void load_alerts_deletion(const std::string &file_path, Spawnables &alerts);
};


#endif //MIGRATION_OFFICE_FILE_H
