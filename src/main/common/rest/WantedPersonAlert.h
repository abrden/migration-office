#ifndef MIGRATION_OFFICE_WANTEDPERSONALERT_H
#define MIGRATION_OFFICE_WANTEDPERSONALERT_H

#include <list>
#include "Feature.h"

class WantedPersonAlert {

    private:
        std::list<Feature*> person_features;
        const size_t id;

    public:
        explicit WantedPersonAlert(const std::list<Feature*>& person_features, const size_t id);
        const std::list<Feature*>& get_features();
        size_t get_id();
        ~WantedPersonAlert();

};


#endif //MIGRATION_OFFICE_WANTEDPERSONALERT_H
