#include "MigrationBooth.h"
#include "SignalHandler.h"

MigrationBooth::MigrationBooth(const int stampers_number, const bool debug, const std::string log_file)
        : logger(debug, log_file),
          queue(logger),
          police(logger),
          stampers(stampers_number) {

    logger(BOOTH) << "Welcome to the Conculandia Migration Booth!" << std::endl;
    logger(BOOTH) << "debug = " << debug << std::endl;
    logger(BOOTH) << "log file = " << log_file << std::endl;

    police.receive_fugitives();

    SignalHandler::get_instance()->register_handler(SIGINT, &sigint_handler);
}

void MigrationBooth::attend_resident(Resident* resident) {
    if (!police.is_fugitive(resident)) {
        logger(BOOTH) << "Welcome to Conculandia, resident " << resident->get_id() << std::endl;
        statistics_communicator.notify_allowed_resident();
    } else {
        police.report(resident);
        statistics_communicator.notify_detained_resident();
    }
    delete resident;
}

void MigrationBooth::attend_foreigner(Foreigner* foreigner) {
    police.receive_alerts();
    if (!police.is_wanted_person(foreigner)) {
        logger(BOOTH) << "Looking available for stamper" << std::endl;
        stampers.get_stamper();
        foreigner->get_passport().stamp_passport(logger);
        logger(BOOTH) << "Welcome to Conculandia, foreigner " << foreigner->get_passport().get_id() << std::endl;
        logger(BOOTH) << "Returning stamper" << std::endl;
        stampers.return_stamper();
        statistics_communicator.notify_allowed_foreigner();
    } else {
        police.report(foreigner);
        statistics_communicator.notify_deported_foreigner();
    }
    delete foreigner;
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
}