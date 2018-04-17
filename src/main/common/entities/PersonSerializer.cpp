#include "PersonSerializer.h"
#include "Foreigner.h"
#include "Resident.h"

#include <sstream>

std::string PersonSerializer::serialize(Person* person) {
    std::stringstream ss;
    if (person->has_id()) {
        ss << '1' << ',';
        Resident* r = (Resident*) person;
        ss << r->get_id();
    } else {
        ss << '0' << ',';
        Foreigner* f = (Foreigner*) person;
        ss << f->get_passport().get_id();
    }
    std::list<Feature*> features = person->get_features();
    for (std::list<Feature*>::iterator iterator = features.begin(), end = features.end(); iterator != end; ++iterator) {
        ss << ',';
        ss << (*iterator)->get_feature();
    }


    return ss.str();
}