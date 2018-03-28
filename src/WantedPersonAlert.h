#ifndef MIGRATION_OFFICE_WANTEDPERSONALERT_H
#define MIGRATION_OFFICE_WANTEDPERSONALERT_H

#include <list>
#include "Feature.h"

class WantedPersonAlert {

    private:
        const std::list<Feature*> personFeatures;

    public:
        WantedPersonAlert(std::list<Feature*> personFeatures);
        const std::list<Feature*> getFeatures();
        ~WantedPersonAlert();

};


#endif //MIGRATION_OFFICE_WANTEDPERSONALERT_H
