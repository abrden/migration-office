#ifndef MIGRATION_OFFICE_FILE_H
#define MIGRATION_OFFICE_FILE_H

#include <vector>
#include <list>

#include "Spawnables.h"
#include "Feature.h"

class ConfigurationFileReader {

    public:
        std::vector<std::string> split_line_into_tokens(std::string& line) const;
        std::list<Feature*> extract_features(std::vector<std::string>& raw_features) const;
        void load_spawnables(const std::string& file_path, Spawnables& persons) const;
        void load_fugitives_ids(const std::string& fugitives_file_path, std::vector<unsigned int> &fugitives_ids) const;

};


#endif //MIGRATION_OFFICE_FILE_H
