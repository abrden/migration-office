#ifndef MIGRATION_OFFICE_STATISTICS_H
#define MIGRATION_OFFICE_STATISTICS_H

#include <cstddef>

class Statistics {

    private:
        size_t residents_allowed;
        size_t residents_detained;
        size_t foreigners_allowed;
        size_t foreigners_deported;
    public:
        Statistics();
        size_t get_allowed_residents() const;
        size_t get_detained_residents() const;
        size_t get_allowed_foreigners() const;
        size_t get_deported_foreigners() const;

};

#endif //MIGRATION_OFFICE_STATISTICS_H
