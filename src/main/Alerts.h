#ifndef MIGRATION_OFFICE_ALERTS_H
#define MIGRATION_OFFICE_ALERTS_H


#include "WantedPersonAlert.h"
#include "Spawnables.h"

class Alerts : public Spawnables {

    public:
        void push_alert(int timestamp, WantedPersonAlert* alert);
        ~Alerts();

};


#endif //MIGRATION_OFFICE_ALERTS_H
