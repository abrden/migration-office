#ifndef MIGRATION_OFFICE_FOREIGNER_H
#define MIGRATION_OFFICE_FOREIGNER_H

#include "Person.h"
#include "Passport.h"

class Foreigner : public Person {

    private:
        const Passport passport;

    public:
        Foreigner(Passport passport, std::list<Feature*> features);
        const Passport get_passport();
        bool has_id() override;
};


#endif //MIGRATION_OFFICE_FOREIGNER_H
