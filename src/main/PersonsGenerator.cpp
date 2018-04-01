#include "PersonsGenerator.h"
#include "Resident.h"
#include "Foreigner.h"

#include <fstream>
#include <sstream>
#include <list>

std::vector<std::string> get_next_line_and_split_into_tokens(std::istream &str)
{
    std::vector<std::string> result;
    std::string line;
    std::getline(str,line);

    std::stringstream lineStream(line);
    std::string cell;

    while(std::getline(lineStream,cell, ','))
    {
        result.push_back(cell);
    }
    // This checks for a trailing comma with no data after it.
//    if (!lineStream && cell.empty())
//    {
//        // If there was a trailing comma then add an empty element.
//        result.push_back("");
//    }
    return result;
}

std::list<Feature*> extract_features(std::vector<std::string> raw_features) {
    std::list<Feature*> l;
    for(auto const& i : raw_features) l.push_back(new Feature(i));
    return l;
}

PersonsGenerator::PersonsGenerator(const std::string& persons_file_path) {
    std::ifstream ifs(persons_file_path);
    std::string line;

    while (getline(ifs, line)) {

        std::vector<std::string> tokenized_line = get_next_line_and_split_into_tokens(ifs);

        // TODO don't use magic numbers, define them in a enum
//        int timestamp = stoi(tokenized_line[0]);
        bool resident = stoi(tokenized_line[1]) == 1;
        auto id = (unsigned int) stoi(tokenized_line[2]);
        std::string name = tokenized_line[3];
        std::string last_name = tokenized_line[4];
        std::vector<std::string> raw_features(tokenized_line.begin() + 5, tokenized_line.end());
        std::list<Feature*> person_features = extract_features(raw_features);

        if (resident) {
            persons.push(new Resident(id, person_features));
        } else {
            persons.push(new Foreigner(Passport(), person_features));
        }
    }

//    persons.sort(order_by_timestamp);
}

PersonsGenerator::~PersonsGenerator() {
    while(!persons.empty()) {
        delete persons.front();
        persons.pop();
    }

}
