#include "MigrationBooth.h"
#include "SignalHandler.h"

MigrationBooth::MigrationBooth(const bool debug, const std::string log_file) : logger(debug, log_file),
                                                                               queue(logger),
                                                                               police(logger) {

    logger(BOOTH) << "Welcome to the Conculandia Migration Booth!" << std::endl;
    logger(BOOTH) << "debug = " << debug << std::endl;
    logger(BOOTH) << "log file = " << log_file << std::endl;

    SignalHandler::get_instance()->register_handler(SIGINT, &sigint_handler);
    SignalHandler::get_instance()->register_handler(SIGUSR1, &sigusr_handler);
}

void MigrationBooth::attend_resident(Resident* resident) {
    if (!police.is_fugitive(resident)) {
        logger(BOOTH) << "Welcome to Conculandia, resident " << resident->get_id() << std::endl;
        arrived_residents.emplace_back(resident);
        statistics_communicator.notify_allowed_resident();
    } else {
        police.report(resident);
        statistics_communicator.notify_detained_resident();
    }
}

void MigrationBooth::attend_foreigner(Foreigner* foreigner) {
    while (sigusr_handler.get_news_available() == 1) {
        police.receive_alert();
        sigusr_handler.reset();
    }
    if (!police.is_wanted_person(foreigner)) {
        Stamper* stamper = stampers.get_stamper();
        foreigner->get_passport().stamp_passport(stamper);
        logger(BOOTH) << "Welcome to Conculandia, foreigner " << foreigner->get_passport().get_id() << std::endl;
        arrived_foreigners.emplace_back(foreigner);
        statistics_communicator.notify_allowed_foreigner();
    } else {
        police.report(foreigner);
        statistics_communicator.notify_deported_foreigner();
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