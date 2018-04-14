#include <iostream>

#include "Police.h"

// TODO review this
const std::string FILE_NAME = "/bin/ls";
const char LETTER = 'A';

Police::Police() : sm(FILE_NAME, LETTER) {
    fugitives = sm.read();
    std::cout << "I'm the prestigious Policia Bonaerense, I received " << fugitives.size() << " fugitives ids" << std::endl;
}

bool Police::is_fugitive(Resident* resident) {
    // TODO
    return false;
}

bool Police::is_wanted_person(Foreigner* foreigner) {
    // TODO
    return false;
}

void Police::report(Resident* resident) {
    // TODO
    std::cout << "Resident " << resident->get_id() << " you are arrested" << std::endl;
}

