#ifndef MIGRATION_OFFICE_WANTEDPERSONSLIST_H
#define MIGRATION_OFFICE_WANTEDPERSONSLIST_H


#include "WantedPersonAlert.h"

class WantedPersonsList {

    private:
        std::list<WantedPersonAlert*> list;

    public:
        void add_alert(WantedPersonAlert* alert);
        ~WantedPersonsList();

};


#endif //MIGRATION_OFFICE_WANTEDPERSONSLIST_H
