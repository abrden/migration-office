#ifndef MIGRATION_OFFICE_STATISTICSDATA_H
#define MIGRATION_OFFICE_STATISTICSDATA_H

#include <cstddef>

typedef struct {
    size_t allowed_residents;
    size_t detained_residents;
    size_t allowed_foreigners;
    size_t deported_foreigners;
} Data;

#endif //MIGRATION_OFFICE_STATISTICSDATA_H
