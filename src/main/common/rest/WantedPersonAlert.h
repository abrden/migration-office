#ifndef MIGRATION_OFFICE_WANTEDPERSONALERT_H
#define MIGRATION_OFFICE_WANTEDPERSONALERT_H

#include <list>
#include "src/main/common/entities/Feature.h"
#include "Spawnable.h"

class WantedPersonAlert : public Spawnable {

    private:
        std::list<Feature*> person_features;

    public:
        explicit WantedPersonAlert(const std::list<Feature*>& person_features);
        const std::list<Feature*>& get_features();
        ~WantedPersonAlert();

};


#endif //MIGRATION_OFFICE_WANTEDPERSONALERT_H
