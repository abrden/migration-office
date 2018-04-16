#include "MigrationOffice.h"

#include <unistd.h>
#include <vector>
#include <sys/wait.h>
#include <system_error>
#include <iostream>

#include "SignalHandler.h"

const static std::string booth_binary = "./migration_booth";
const static std::string spawner_binary = "./migration_spawner";

MigrationOffice::MigrationOffice(const int booths_number, const int stampers_number,
                                 const std::string people_file, const std::string alerts_file,
                                 const std::string fugitives_file,
                                 const bool debug, const std::string log_file)
        : booths_number(booths_number), stampers_number(stampers_number),
          people_file(people_file), alerts_file(alerts_file), fugitives_file(fugitives_file),
          debug(debug), log_file(log_file) {

    SignalHandler::get_instance()->register_handler(SIGINT, &sigint_handler);
}



void MigrationOffice::open_booths() {
    for (int i = 0; i < booths_number; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            throw std::system_error(errno, std::generic_category());
        } else if (pid > 0) {
            children_pids.emplace_back(pid);
        } else {
            std::string debug_flag = debug ? "1" : "0";

            std::vector<char*> booth_argv;
            booth_argv.push_back(const_cast<char*>(booth_binary.c_str()));
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
        throw std::system_error(errno, std::generic_category());
    } else if (pid > 0) {
        children_pids.emplace_back(pid);
    } else {
        std::string debug_flag = debug ? "1" : "0";

        std::vector<char*> spawner_argv;
        spawner_argv.push_back(const_cast<char*>(spawner_binary.c_str()));
        spawner_argv.push_back(const_cast<char*>(people_file.c_str()));
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
    SignalHandler::destroy();
}