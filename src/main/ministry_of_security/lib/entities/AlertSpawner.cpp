#include "AlertSpawner.h"

#include "SignalHandler.h"

AlertSpawner::AlertSpawner(Logger& logger, const std::string& alerts_file) : Spawner(logger, alerts), logger(logger) {
    ConfigurationFileReader::load_spawnables(alerts_file, alerts);

    SignalHandler::get_instance()->register_handler(SIGINT, &sigint_handler);
}

void AlertSpawner::spawn(std::string spawnable) {
    // TODO
}

bool AlertSpawner::quit() {
    return sigint_handler.get_graceful_quit() == 1;
}

AlertSpawner::~AlertSpawner() {
    SignalHandler::destroy();
}