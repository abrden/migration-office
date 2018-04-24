#ifndef MIGRATION_OFFICE_PASSPORT_H
#define MIGRATION_OFFICE_PASSPORT_H

#include <string>
#include "Logger.h"

class Passport {

    private:
        const std::string id;

    public:
        explicit Passport(const std::string& id);
        void stamp_passport(Logger& logger);
        const std::string& get_id();
        ~Passport();

};

#endif //MIGRATION_OFFICE_PASSPORT_H
