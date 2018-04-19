#ifndef MIGRATION_OFFICE_LOGGER_H
#define MIGRATION_OFFICE_LOGGER_H

#include <string>

#include "ExclusiveLock.h"

class Logger {

    private:
        const std::string file;
        ExclusiveLock lock;

    public:
        explicit Logger(const std::string& file);
        Logger& operator<<(const std::string& message);

};


#endif //MIGRATION_OFFICE_LOGGER_H