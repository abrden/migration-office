#include "MigrationBooth.h"

MigrationBooth::MigrationBooth(const std::string people_file, const std::string alerts_file,
                               const std::string fugitives_file,
                               const bool debug, const std::string log_file)
        : people_file(people_file), alerts_file(alerts_file), fugitives_file(fugitives_file),
          debug(debug), log_file(log_file) {}