#include "MigrationOffice.h"
#include "SignalHandler.h"
#include "FileNames.h"

#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
#include <system_error>

MigrationOffice::MigrationOffice(const int booths_number, const int stampers_number,
                                 const std::string people_file, const std::string alerts_file,
                                 const std::string fugitives_file,
                                 const bool debug, const std::string log_file)
        : booths_number(booths_number), stampers_number(stampers_number),
          people_file(people_file), alerts_file(alerts_file), fugitives_file(fugitives_file),
          debug(debug), log_file(log_file), logger(debug, log_file) {

    logger(OFFICE) << "Welcome to the Conculandia Migration Office!" << std::endl;
    logger(OFFICE) << "booths number = " << booths_number << std::endl;
    logger(OFFICE) << "stampers number = " << stampers_number << std::endl;
    logger(OFFICE) << "people file = " << people_file << std::endl;
    logger(OFFICE) << "alerts file = " << alerts_file << std::endl;
    logger(OFFICE) << "fugitives file = " << fugitives_file << std::endl;
    logger(OFFICE) << "debug = " << debug << std::endl;
    logger(OFFICE) << "log file = " << log_file << std::endl;

    SignalHandler::get_instance()->register_handler(SIGINT, &sigint_handler);
}

void MigrationOffice::start() {
    open_statistics();
    open_booths();
    open_ministry_of_security();
    fork_spawner();
    open_alert_deleter();
}

void MigrationOffice::open_ministry_of_security() {
    pid_t pid = fork();

    if (pid < 0) {
        throw std::system_error(errno, std::system_category());
    } else if (pid > 0) {
        children_pids.push_back(pid);
    } else {
        std::string debug_flag = debug ? "1" : "0";

        std::vector<char*> booth_argv;
        booth_argv.push_back(const_cast<char*>(BinaryNames::MINISTER_BINARY.c_str()));
        booth_argv.push_back(const_cast<char*>(alerts_file.c_str()));
        booth_argv.push_back(const_cast<char*>(fugitives_file.c_str()));
        booth_argv.push_back(const_cast<char*>(debug_flag.c_str()));
        booth_argv.push_back(const_cast<char*>(log_file.c_str()));
        std::string booths_number_str = std::to_string(booths_number);
        booth_argv.push_back(const_cast<char*>(booths_number_str.c_str()));

        std::vector<std::string> pids_str;
        for (int i = 0; i < booths_number; i++) {
            std::string pid_str = std::to_string(booth_pids.at(i));
            pids_str.emplace_back(pid_str);
        }

        for (int i = 0; i < booths_number; i++) {
            booth_argv.push_back(const_cast<char *>(pids_str.at(i).c_str()));
        }

        booth_argv.push_back(nullptr);

        execv(booth_argv[0], &booth_argv[0]);
    }
}

void MigrationOffice::open_booths() {
    for (int i = 0; i < booths_number; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            throw std::system_error(errno, std::system_category());
        } else if (pid > 0) {
            children_pids.push_back(pid);
            booth_pids.push_back(pid);
        } else {
            std::string debug_flag = debug ? "1" : "0";

            std::vector<char*> booth_argv;
            booth_argv.push_back(const_cast<char*>(BinaryNames::BOOTH_BINARY.c_str()));
            booth_argv.push_back(const_cast<char*>(debug_flag.c_str()));
            booth_argv.push_back(const_cast<char*>(log_file.c_str()));
            booth_argv.push_back(nullptr);

            execv(booth_argv[0], &booth_argv[0]);
        }
    }
}

void MigrationOffice::fork_spawner() {
    pid_t pid = fork();

    if (pid < 0) {
        throw std::system_error(errno, std::system_category());
    } else if (pid > 0) {
        children_pids.emplace_back(pid);
    } else {
        std::string debug_flag = debug ? "1" : "0";

        std::vector<char*> spawner_argv;
        spawner_argv.push_back(const_cast<char*>(BinaryNames::SPAWNER_BINARY.c_str()));
        spawner_argv.push_back(const_cast<char*>(people_file.c_str()));
        spawner_argv.push_back(const_cast<char*>(debug_flag.c_str()));
        spawner_argv.push_back(const_cast<char*>(log_file.c_str()));
        spawner_argv.push_back(nullptr);

        execv(spawner_argv[0], &spawner_argv[0]);
    }
}

void MigrationOffice::open_statistics() {
    pid_t pid = fork();

    if (pid < 0) {
        throw std::system_error(errno, std::system_category());
    } else if (pid > 0) {
        children_pids.emplace_back(pid);
    } else {
        std::string debug_flag = debug ? "1" : "0";

        std::vector<char*> spawner_argv;
        spawner_argv.push_back(const_cast<char*>(BinaryNames::STATISTICS_BINARY.c_str()));
        spawner_argv.push_back(const_cast<char*>(debug_flag.c_str()));
        spawner_argv.push_back(const_cast<char*>(log_file.c_str()));
        spawner_argv.push_back(const_cast<char*>(std::to_string(booths_number).c_str()));
        spawner_argv.push_back(nullptr);

        execv(spawner_argv[0], &spawner_argv[0]);
    }
}

void MigrationOffice::open_alert_deleter() {
    pid_t pid = fork();

    if (pid < 0) {
        throw std::system_error(errno, std::system_category());
    } else if (pid > 0) {
        children_pids.emplace_back(pid);
    } else {
        std::string debug_flag = debug ? "1" : "0";

        std::vector<char*> spawner_argv;
        spawner_argv.push_back(const_cast<char*>(BinaryNames::ALERT_DELETER_BINARY.c_str()));
        spawner_argv.push_back(const_cast<char*>(alerts_file.c_str()));
        spawner_argv.push_back(const_cast<char*>(debug_flag.c_str()));
        spawner_argv.push_back(const_cast<char*>(log_file.c_str()));
        spawner_argv.push_back(nullptr);

        execv(spawner_argv[0], &spawner_argv[0]);
    }
}

void MigrationOffice::wait_children() {
    while (!children_pids.empty()) {
        pid_t child_pid = wait(nullptr);
        children_pids.remove(child_pid);
    }
}

MigrationOffice::~MigrationOffice() {
    wait_children();
    SignalHandler::destroy();
    logger(OFFICE) << "========== CLOSED ==========" << std::endl;
}