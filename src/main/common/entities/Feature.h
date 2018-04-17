#ifndef MIGRATION_OFFICE_FEATURE_H
#define MIGRATION_OFFICE_FEATURE_H

#include <string>

class Feature {

    private:
        const std::string feature;

    public:
        explicit Feature(std::string feature);
        const std::string& get_feature();
        ~Feature();

};

#endif //MIGRATION_OFFICE_FEATURE_H
