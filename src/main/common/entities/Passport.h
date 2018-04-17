#ifndef MIGRATION_OFFICE_PASSPORT_H
#define MIGRATION_OFFICE_PASSPORT_H

#include <string>

#include "Stamper.h"

class Passport {

    private:
        const std::string id;

    public:
        explicit Passport(const std::string& id);
        void stamp_passport(Stamper* stamper);
        const std::string& get_id();
        ~Passport();

};

#endif //MIGRATION_OFFICE_PASSPORT_H
