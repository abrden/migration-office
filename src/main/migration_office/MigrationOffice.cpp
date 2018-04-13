#include <unistd.h>
#include <vector>
#include <sys/wait.h>

#include "MigrationOffice.h"

MigrationOffice::MigrationOffice(const int booths_number, const int stampers_number,
                                 const std::string people_file, const std::string alerts_file,
                                 const std::string fugitives_file,
                                 const bool debug, const std::string log_file)
        : booths_number(booths_number), stampers_number(stampers_number),
          people_file(people_file), alerts_file(alerts_file), fugitives_file(fugitives_file),
          debug(debug), log_file(log_file) {}



void MigrationOffice::open_booths() {
    for (int i = 0; i < booths_number; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("FORK FAILED\n");
            return;
        } else if (pid > 0) {
            booths_pids.emplace_back(pid);
        } else {
            std::string debug_flag = debug ? "1" : "0";

            std::vector<char*> booth_argv;
            booth_argv.push_back(const_cast<char*>(people_file.c_str()));
            booth_argv.push_back(const_cast<char*>(alerts_file.c_str()));
            booth_argv.push_back(const_cast<char*>(fugitives_file.c_str()));
            booth_argv.push_back(const_cast<char*>(debug_flag.c_str()));
            booth_argv.push_back(const_cast<char*>(log_file.c_str()));
            booth_argv.push_back(NULL);

            execv("./migration_booth", &booth_argv[0]);
        }
    }
}

void MigrationOffice::wait_booths() {
    while (!booths_pids.empty()) {
        pid_t child_pid = wait(nullptr);
        booths_pids.remove(child_pid);
    }
}

MigrationOffice::~MigrationOffice() {}