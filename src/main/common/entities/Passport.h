#ifndef MIGRATION_OFFICE_PASSPORT_H
#define MIGRATION_OFFICE_PASSPORT_H

#include <string>

#include "Stamper.h"

class Passport {

    private:
        const std::string id;

    public:
        Passport(std::string& id);
        void stamp_passport(Stamper& stamper);
        ~Passport();

};

#endif //MIGRATION_OFFICE_PASSPORT_H
