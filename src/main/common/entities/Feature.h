#ifndef MIGRATION_OFFICE_FEATURE_H
#define MIGRATION_OFFICE_FEATURE_H

#include <string>

class Feature {

    private:
        const std::string feature;

    public:
        explicit Feature(std::string feature);
        ~Feature() = default;

};

#endif //MIGRATION_OFFICE_FEATURE_H
