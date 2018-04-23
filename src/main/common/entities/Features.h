#ifndef MIGRATION_OFFICE_FEATURE_H
#define MIGRATION_OFFICE_FEATURE_H

#include <list>
#include <string>

class Features {

    private:
        const std::list<std::string> features;

    public:
        explicit Features(const std::list<std::string>& features);
        bool operator==(const Features& other) const;
        ~Features();

};

#endif //MIGRATION_OFFICE_FEATURE_H
