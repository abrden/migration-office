#include "MinisterOfSecurity.h"
#include "ConfigurationFileReader.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include "ExclusiveLock.h"

const std::string FILE_NAME = "/bin/ls";
const char LETTER = 'A';

MinisterOfSecurity::MinisterOfSecurity(const std::string& alerts_file_path,
                                       const std::string& fugitives_file_path) {
    ConfigurationFileReader fr;
    fr.load_alerts(alerts_file_path, alerts);
    fr.load_fugitives_ids(fugitives_file_path, fugitives);
}

Spawnables& MinisterOfSecurity::get_alerts() {
    return alerts;
}

void MinisterOfSecurity::send_fugitives() {
    ExclusiveLock l("../.gitignore");
    l.lock();
    std::cout << "I'm the prestigious Pato Bullrich and I'm sending " << fugitives.size() << " fugitives!" << std::endl;
    l.unlock();
}
