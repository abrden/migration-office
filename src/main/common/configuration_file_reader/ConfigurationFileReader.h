#ifndef MIGRATION_OFFICE_FILE_H
#define MIGRATION_OFFICE_FILE_H

#include <vector>
#include <list>

#include "Spawnables.h"
#include "Feature.h"

class ConfigurationFileReader {

    private:
        std::vector<std::string> split_line_into_tokens(std::string& line);
        std::list<Feature*> extract_features(std::vector<std::string>& raw_features);

    public:
        void load_fugitives_ids(const std::string& fugitives_file_path, std::list<std::string>& fugitives_ids);
        void load_spawnables(const std::string& file_path, Spawnables& persons);

};


#endif //MIGRATION_OFFICE_FILE_H
