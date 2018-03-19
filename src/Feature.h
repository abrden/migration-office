#ifndef MIGRATION_OFFICE_FEATURE_H
#define MIGRATION_OFFICE_FEATURE_H

#include <string>

class Feature {

    private:
        const std::string feature;

    public:
        explicit Feature(std::string feature);
        const std::string getFeature();
        ~Feature();

};

#endif //MIGRATION_OFFICE_FEATURE_H
