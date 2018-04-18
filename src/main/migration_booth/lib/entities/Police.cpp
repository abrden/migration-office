#include <iostream>

#include "Police.h"

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
    std::cout << "[POLICE] Resident " << resident->get_id() << " you are arrested" << std::endl;
}

void Police::add_fugitive(const unsigned int id) {}
