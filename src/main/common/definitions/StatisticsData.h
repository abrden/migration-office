#ifndef MIGRATION_OFFICE_STATISTICSDATA_H
#define MIGRATION_OFFICE_STATISTICSDATA_H

#include <cstddef>

enum FIELDS {
    ALLOWED_RESIDENTS,
    DETAINED_RESIDENTS,
    ALLOWED_FOREIGNERS,
    DEPORTED_FOREIGNERS
};

typedef struct {
    size_t allowed_residents;
    size_t detained_residents;
    size_t allowed_foreigners;
    size_t deported_foreigners;
} StatisticsData;

#endif //MIGRATION_OFFICE_STATISTICSDATA_H