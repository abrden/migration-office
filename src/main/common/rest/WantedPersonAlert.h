#ifndef MIGRATION_OFFICE_WANTEDPERSONALERT_H
#define MIGRATION_OFFICE_WANTEDPERSONALERT_H

#include <list>
#include <string>

class WantedPersonAlert {

    private:
        std::list<std::string> person_features;
        const size_t id;

    public:
        explicit WantedPersonAlert(const std::list<std::string>& person_features, const size_t id);
        const std::list<std::string>& get_features();
        size_t get_id();
        ~WantedPersonAlert();

};


#endif //MIGRATION_OFFICE_WANTEDPERSONALERT_H
