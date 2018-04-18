#include <fstream>
#include <sstream>
#include <vector>

#include "ConfigurationFileReader.h"

const static char SEPARATOR = ',';

std::vector<std::string> ConfigurationFileReader::split_line_into_tokens(std::string& line) const {
    std::vector<std::string> result;

    std::stringstream lineStream(line);
    std::string cell;

    while (std::getline(lineStream, cell, SEPARATOR)) {
        result.push_back(cell);
    }
    return result;
}

std::list<Feature*> ConfigurationFileReader::extract_features(std::vector<std::string>& raw_features) const {
    std::list<Feature*> l;
    for (auto const &i : raw_features) l.push_back(new Feature(i));
    return l;
}

void ConfigurationFileReader::load_fugitives_ids(const std::string& fugitives_file_path,
                                                 std::vector<unsigned int> &fugitives_ids) const {
    // TODO add exception handling
    std::ifstream ifs(fugitives_file_path);
    std::string fugitive_id;

    // Get header
    std::getline(ifs, fugitive_id);
    while (std::getline(ifs, fugitive_id)) {
        fugitives_ids.push_back(std::stoi(fugitive_id));
    }
}

void ConfigurationFileReader::load_spawnables(const std::string& file_path, Spawnables& persons) const {
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