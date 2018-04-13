#include "MigrationBooth.h"

#include "SignalHandler.h"

#include <iostream>
#include <unistd.h>

MigrationBooth::MigrationBooth(const std::string people_file, const std::string alerts_file,
                               const std::string fugitives_file,
                               const bool debug, const std::string log_file)
        : people_file(people_file), alerts_file(alerts_file), fugitives_file(fugitives_file),
          debug(debug), log_file(log_file) {

    SignalHandler::get_instance()->register_handler(SIGINT, &sigint_handler);
}

void MigrationBooth::attend_resident(Resident* resident) {
    if (!police.is_fugitive(resident)) {
        std::cout << "Welcome to Conculandia, resident " << resident->get_id() << std::endl;
        arrived_residents.emplace_back(resident);
    } else {
        police.report(resident);
    }
}

void MigrationBooth::attend_foreigner(Foreigner* foreigner) {
    if (police.is_wanted_person(foreigner)) {
        std::cout << "Foreigner " << foreigner->get_passport().get_id() << " you are deported" << std::endl;
    } else {
        Stamper* stamper = stampers.get_stamper();
        foreigner->get_passport().stamp_passport(stamper);
        std::cout << "Welcome to Conculandia foreigner " << foreigner->get_passport().get_id() << std::endl;
        arrived_foreigners.emplace_back(foreigner);
    }
}

void MigrationBooth::open() {
    while (sigint_handler.get_graceful_quit() == 0) {
        Person* person = queue.front();
        if (person->has_id())
            attend_resident((Resident*)person);
        else
            attend_foreigner((Foreigner*)person);
        sleep(2); // FIXME sleepy sleep to avoid killing my cpu
    }
    SignalHandler::destroy();
}

MigrationBooth::~MigrationBooth() {
    while (!arrived_residents.empty()) {
        delete arrived_residents.back();
        arrived_residents.pop_back();
    }
    while (!arrived_foreigners.empty()) {
        delete arrived_foreigners.back();
        arrived_foreigners.pop_back();
    }
}