#ifndef MIGRATION_OFFICE_LOGGER_H
#define MIGRATION_OFFICE_LOGGER_H

#include <sstream>
#include <string>

#include "ExclusiveLock.h"

class Logger {

    private:
        std::string file;
        ExclusiveLock lock;
        std::ostringstream oss;

    public:
        explicit Logger(const bool debug, const std::string& file);
        template <typename T>
        Logger& operator<<(T a) {
            oss << a;
            return *this;
        }
        typedef std::ostream&(*io_manip_ptr_t)(std::ostream&);
        Logger& operator<<(io_manip_ptr_t f);

};


#endif //MIGRATION_OFFICE_LOGGER_H