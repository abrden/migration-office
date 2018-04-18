#include <fstream>
#include <sstream>
#include <vector>

#include "ConfigurationFileReader.h"
#include "WantedPersonAlert.h"
#include "Resident.h"
#include "Foreigner.h"

const static char SEPARATOR = ',';

enum ALERTS_FIELDS {
    alert_timestamp = 0,
    alert_features_start = 1
};

enum PEOPLE_FIELDS {
    person_timestamp,
    person_resident,
    person_id,
    person_passport_id,
    person_name,
    person_last_name,
    person_features_start
};

std::vector<std::string> ConfigurationFileReader::split_line_into_tokens(std::string& line) {
    std::vector<std::string> result;

    std::stringstream lineStream(line);
    std::string cell;

    while (std::getline(lineStream, cell, SEPARATOR)) {
        result.push_back(cell);
    }
    return result;
}

std::list<Feature*> ConfigurationFileReader::extract_features(std::vector<std::string>& raw_features) {
    std::list<Feature*> l;
    for (auto const &i : raw_features) l.push_back(new Feature(i));
    return l;
}

void ConfigurationFileReader::load_fugitives_ids(const std::string& fugitives_file_path, std::list<std::string>& fugitives_ids) {
    // TODO add exception handling
    std::ifstream ifs(fugitives_file_path);
    std::string fugitive_id;

    // Get header
    std::getline(ifs, fugitive_id);
    while (std::getline(ifs, fugitive_id)) {
        fugitives_ids.emplace_back(fugitive_id);
    }
}

void ConfigurationFileReader::load_spawnables(const std::string& file_path, Spawnables& persons) {
    // TODO add exception handling
    std::ifstream ifs(file_path);
    std::string line;

    // Get header
    std::getline(ifs, line);

    while (std::getline(ifs, line)) {
        std::stringstream line_stream(line);

        std::string timestamp;
        std::getline(line_stream, timestamp, SEPARATOR);

        std::string serialized_spawnable;
        getline(line_stream, serialized_spawnable);

        persons.push_spawnable(stoi(timestamp), serialized_spawnable);
    }
}