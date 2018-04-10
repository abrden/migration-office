#include "Stamper.h"
#include "MigrationBooth.h"

#include <iostream>

MigrationBooth::MigrationBooth(const std::string people_file, const std::string alerts_file,
                               const std::string fugitives_file,
                               const bool debug, const std::string log_file)
        : people_file(people_file), alerts_file(alerts_file), fugitives_file(fugitives_file),
          debug(debug), log_file(log_file) {}

bool MigrationBooth::is_fugitive(Resident* resident) {
    // TODO
    return false;
}

void MigrationBooth::report_to_police(Resident* resident) {
    // TODO
    std::cout << "Resident " << resident->get_id() << " you are arrested" << std::endl;
}

void MigrationBooth::attend_resident(Resident* resident) {
    if (!is_fugitive(resident)) {
        std::cout << "Welcome to Conculandia, resident " << resident->get_id() << std::endl;
        arrived_residents.emplace_back(resident);
    } else {
        report_to_police(resident);
    }
}

bool MigrationBooth::is_wanted_person(Foreigner* foreigner) {
    // TODO
    return false;
}

Stamper* MigrationBooth::get_stamper() {
    // TODO
    return new Stamper();
}

void MigrationBooth::attend_foreigner(Foreigner* foreigner) {
    if (is_wanted_person(foreigner)) {
        std::cout << "Foreigner " << foreigner->get_passport().get_id() << " you are deported" << std::endl;
    } else {
        Stamper* stamper = get_stamper();
        foreigner->get_passport().stamp_passport(*stamper);
        std::cout << "Welcome to Conculandia foreigner " << foreigner->get_passport().get_id() << std::endl;
        arrived_foreigners.emplace_back(foreigner);
    }
}

void MigrationBooth::open() {
    while (!queue.empty()) {
        Person* person = queue.front();
        if (person->has_id())
            attend_resident((Resident*)person);
        else
            attend_foreigner((Foreigner*)person);
    }
}