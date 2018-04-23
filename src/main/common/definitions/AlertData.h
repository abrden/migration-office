#ifndef MIGRATION_OFFICE_ALERTDATA_H
#define MIGRATION_OFFICE_ALERTDATA_H

#include <stddef.h>

const static size_t BUFFSIZE = 1024;

typedef struct {
    size_t id;
    char serialized_alert[BUFFSIZE];
    size_t serialized_alert_size;
    size_t read_by_quantity;
} AlertData;

#endif //MIGRATION_OFFICE_ALERTDATA_H
