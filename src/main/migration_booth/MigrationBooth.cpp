#include "MigrationBooth.h"
#include "SignalHandler.h"

#include <iostream>

MigrationBooth::MigrationBooth(const bool debug, const std::string log_file) : logger(debug, log_file) {
    SignalHandler::get_instance()->register_handler(SIGINT, &sigint_handler);
}

void MigrationBooth::attend_resident(Resident* resident) {
    if (!police.is_fugitive(resident)) {
        std::cout << "[BOOTH] Welcome to Conculandia, resident " << resident->get_id() << std::endl;
        logger << "Welcome to Conculandia, resident " << resident->get_id() << std::endl;
        arrived_residents.emplace_back(resident);
    } else {
        police.report(resident);
    }
}

void MigrationBooth::attend_foreigner(Foreigner* foreigner) {
    if (!police.is_wanted_person(foreigner)) {
        Stamper* stamper = stampers.get_stamper();
        foreigner->get_passport().stamp_passport(stamper);
        std::cout << "[BOOTH] Welcome to Conculandia foreigner " << foreigner->get_passport().get_id() << std::endl;
        logger << "Welcome to Conculandia, foreigner " << foreigner->get_passport().get_id() << std::endl;
        arrived_foreigners.emplace_back(foreigner);
    } else {
        police.report(foreigner);
    }
}

void MigrationBooth::open() {
    Person* person;
    while ((person = queue.front()) != nullptr && sigint_handler.get_graceful_quit() == 0) {
        if (person->has_id())
            attend_resident((Resident*)person);
        else
            attend_foreigner((Foreigner*)person);
    }
}

MigrationBooth::~MigrationBooth() {
    SignalHandler::destroy();
    while (!arrived_residents.empty()) {
        delete arrived_residents.back();
        arrived_residents.pop_back();
    }

    while (!arrived_foreigners.empty()) {
        delete arrived_foreigners.back();
        arrived_foreigners.pop_back();
    }
}