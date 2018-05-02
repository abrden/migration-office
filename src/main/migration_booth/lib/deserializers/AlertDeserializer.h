#ifndef MIGRATION_OFFICE_ALERTDESERIALIZER_H
#define MIGRATION_OFFICE_ALERTDESERIALIZER_H


#include "WantedPersonAlert.h"

class AlertDeserializer {

    public:
        static WantedPersonAlert* deserialize(std::string& serialized_alert, const size_t id);

};


#endif //MIGRATION_OFFICE_ALERTDESERIALIZER_H
