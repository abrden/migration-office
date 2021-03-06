#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>
#include <stdexcept>


#include "ConfigurationFileReader.h"

const static char SEPARATOR = ',';

std::vector<std::string> ConfigurationFileReader::split_line_into_tokens(std::string& line) {
    std::vector<std::string> result;

    std::stringstream lineStream(line);
    std::string cell;

    while (std::getline(lineStream, cell, SEPARATOR)) {
        result.push_back(cell);
    }
    return result;
}

std::list<std::string> ConfigurationFileReader::extract_features(std::vector<std::string>& raw_features) {
    std::list<std::string> features;
    std::copy(raw_features.begin(), raw_features.end(), std::back_inserter(features));
    return features;
}

void ConfigurationFileReader::load_fugitives_ids(const std::string& fugitives_file_path,
                                                 std::vector<unsigned int> &fugitives_ids) {
    std::ifstream ifs(fugitives_file_path);
    if (!ifs) {
        const std::string message = std::string("Error when opening fugitives configuration file: ") +
                fugitives_file_path + std::string(". ") +
                std::string(strerror(errno));
        throw std::runtime_error(message);
    }
    std::string fugitive_id;

    // Get header
    std::getline(ifs, fugitive_id);
    while (std::getline(ifs, fugitive_id)) {
        fugitives_ids.push_back(std::stoi(fugitive_id));
    }
}

void ConfigurationFileReader::load_persons(const std::string &file_path, Spawnables &persons) {
    std::ifstream ifs(file_path);
    if (!ifs) {
        const std::string message = std::string("Error when opening persons configuration file: ") +
                file_path + std::string(". ") +
                std::string(strerror(errno));
        throw std::runtime_error(message);
    }
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
void ConfigurationFileReader::load_alerts(const std::string& file_path, Spawnables& alerts){
    std::ifstream ifs(file_path);
    if (!ifs) {
        const std::string message = std::string("Error when opening alerts configuration file: ") +
                file_path + std::string(". ") +
                std::string(strerror(errno));
        throw std::runtime_error(message);
    }
    std::string line;

    // Get header
    std::getline(ifs, line);

    while (std::getline(ifs, line)) {
        std::stringstream line_stream(line);

        std::string timestamp;
        std::string del_timestamp;
        std::string serialized_spawnable;

        std::getline(line_stream, timestamp, SEPARATOR);
        std::getline(line_stream, del_timestamp, SEPARATOR);
        getline(line_stream, serialized_spawnable);

        alerts.push_spawnable(stoi(timestamp), serialized_spawnable);
    }
}

void ConfigurationFileReader::load_alerts_deletion(const std::string& file_path, Spawnables& alerts){
    std::ifstream ifs(file_path);
    if (!ifs) {
        const std::string message = std::string("Error when opening alerts configuration file: ") +
                file_path + std::string(". ") +
                std::string(strerror(errno));
        throw std::runtime_error(message);
    }
    std::string line;

    // Get header
    std::getline(ifs, line);

    while (std::getline(ifs, line)) {
        std::stringstream line_stream(line);

        std::string timestamp;
        std::string del_timestamp;
        std::string serialized_spawnable;

        std::getline(line_stream, timestamp, SEPARATOR);
        std::getline(line_stream, del_timestamp, SEPARATOR);
        getline(line_stream, serialized_spawnable);

        alerts.push_spawnable(stoi(del_timestamp), serialized_spawnable);
    }
}