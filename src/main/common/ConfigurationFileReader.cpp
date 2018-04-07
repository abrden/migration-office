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
    person_timestamp = 0,
    person_resident = 1,
    person_id = 2,
    person_name = 3,
    person_last_name = 4,
    person_features_start = 5
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

void ConfigurationFileReader::load_alerts(const std::string& alerts_file_path, Spawnables& alerts) {
    // TODO add exception handling
    std::ifstream ifs(alerts_file_path);
    std::string line;

    // Get header
    std::getline(ifs, line);
    while (std::getline(ifs, line)) {
        std::vector<std::string> tokenized_line = split_line_into_tokens(line);

        int timestamp = stoi(tokenized_line[ALERTS_FIELDS::alert_timestamp]);
        std::vector<std::string> raw_features(tokenized_line.begin() + ALERTS_FIELDS::alert_features_start, tokenized_line.end());
        std::list<Feature*> wanted_person_features = extract_features(raw_features);

        alerts.push_spawnable(timestamp, new WantedPersonAlert(wanted_person_features));
    }
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

void ConfigurationFileReader::load_persons(const std::string& people_file_path, Spawnables& persons) {
    // TODO add exception handling
    std::ifstream ifs(people_file_path);
    std::string line;

    // Get header
    std::getline(ifs, line);
    while (std::getline(ifs, line)) {
        std::vector<std::string> tokenized_line = split_line_into_tokens(line);

        int timestamp = stoi(tokenized_line[PEOPLE_FIELDS::person_timestamp]);
        bool resident = stoi(tokenized_line[PEOPLE_FIELDS::person_resident]) == 1;
        unsigned int id = (unsigned int) stoi(tokenized_line[PEOPLE_FIELDS::person_id]);
        std::string name = tokenized_line[PEOPLE_FIELDS::person_name];
        std::string last_name = tokenized_line[PEOPLE_FIELDS::person_last_name];
        std::vector<std::string> raw_features(tokenized_line.begin() + PEOPLE_FIELDS::person_features_start, tokenized_line.end());
        std::list<Feature*> person_features = extract_features(raw_features);

        if (resident) {
            persons.push_spawnable(timestamp, new Resident(id, person_features));
        } else {
            persons.push_spawnable(timestamp, new Foreigner(Passport(), person_features));
        }
    }
}