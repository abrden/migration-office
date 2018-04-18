#include "MigrationOffice.h"

#include <unistd.h>
#include <vector>
#include <sys/wait.h>
#include <system_error>

#include "SignalHandler.h"

const static std::string BOOTH_BINARY = "./migration_booth";
const static std::string SPAWNER_BINARY = "./migration_spawner";
const static std::string MINISTER_BINARY = "./ministry_of_security";

MigrationOffice::MigrationOffice(const int booths_number, const int stampers_number,
                                 const std::string people_file, const std::string alerts_file,
                                 const std::string fugitives_file,
                                 const bool debug, const std::string log_file)
        : booths_number(booths_number), stampers_number(stampers_number),
          people_file(people_file), alerts_file(alerts_file), fugitives_file(fugitives_file),
          debug(debug), log_file(log_file) {

    SignalHandler::get_instance()->register_handler(SIGINT, &sigint_handler);
}


void MigrationOffice::open_ministry_of_security() {
    pid_t pid = fork();

    if (pid < 0) {
        throw std::system_error(errno, std::generic_category());
    } else if (pid > 0) {
        children_pids.push_back(pid);
    } else {
        std::string debug_flag = debug ? "1" : "0";

        std::vector<char*> booth_argv;
        booth_argv.push_back(const_cast<char*>(MINISTER_BINARY.c_str()));
        booth_argv.push_back(const_cast<char*>(alerts_file.c_str()));
        booth_argv.push_back(const_cast<char*>(fugitives_file.c_str()));
        booth_argv.push_back(const_cast<char*>(debug_flag.c_str()));
        booth_argv.push_back(const_cast<char*>(log_file.c_str()));
        booth_argv.push_back(const_cast<char*>(std::to_string(booths_number).c_str()));
        booth_argv.push_back(nullptr);

        execv(booth_argv[0], &booth_argv[0]);
    }
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
            booth_argv.push_back(const_cast<char*>(BOOTH_BINARY.c_str()));
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
        spawner_argv.push_back(const_cast<char*>(SPAWNER_BINARY.c_str()));
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
    wait_children();
    SignalHandler::destroy();
}