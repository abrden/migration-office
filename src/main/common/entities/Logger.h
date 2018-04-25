#ifndef MIGRATION_OFFICE_LOGGER_H
#define MIGRATION_OFFICE_LOGGER_H

#include <sstream>
#include <string>

#include "ExclusiveLock.h"

const std::string OFFICE = "OFFICE";
const std::string BOOTH = "BOOTH";
const std::string BOOTH_POLICE = "POLICE";
const std::string BOOTH_QUEUE = "QUEUE";
const std::string SPAWNER = "SPAWNER";
const std::string PEOPLE_SPAWNER = "PEOPLE SPAWNER";
const std::string STATISTICS = "STATISTICS";
const std::string MINISTER = "MINISTER";
const std::string ALERT_DELETER = "ALERT DELETER";

class Logger {

    private:
        std::string file;
        ExclusiveLock lock;
        std::ostringstream oss;

        const std::string build_log_message();

    public:
        explicit Logger(const bool debug, const std::string& file);
        Logger& operator()(const std::string& transmitter);
        template <typename T>
        Logger& operator<<(T a) {
            oss << a;
            return *this;
        }
        typedef std::ostream&(*io_manip_ptr_t)(std::ostream&);
        Logger& operator<<(io_manip_ptr_t f);

};


#endif //MIGRATION_OFFICE_LOGGER_H