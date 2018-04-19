#ifndef MIGRATION_OFFICE_LOGGER_H
#define MIGRATION_OFFICE_LOGGER_H

#include <sstream>
#include <string>

#include "ExclusiveLock.h"

class Logger {

    private:
        const std::string file;
        ExclusiveLock lock;
        std::ostringstream oss;

    public:
        explicit Logger(const std::string& file);
        template <typename T>
        Logger& operator<<(T& a);
        typedef std::ostream&(*io_manip_ptr_t)(std::ostream&);
        Logger& operator<<(io_manip_ptr_t f);

};


#endif //MIGRATION_OFFICE_LOGGER_H