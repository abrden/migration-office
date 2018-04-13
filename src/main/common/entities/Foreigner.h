#ifndef MIGRATION_OFFICE_FOREIGNER_H
#define MIGRATION_OFFICE_FOREIGNER_H

#include "Person.h"
#include "Passport.h"

class Foreigner : public Person {

    private:
        Passport passport;

    public:
        Foreigner(Passport passport, std::list<Feature*> features);
        Passport& get_passport();
        bool has_id() override;
};


#endif //MIGRATION_OFFICE_FOREIGNER_H
