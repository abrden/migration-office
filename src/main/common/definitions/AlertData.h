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

const static size_t SERIALIZED_ALERT_SIZE = sizeof(size_t) * 3 + sizeof(char) * BUFFSIZE;

typedef char SerializedAlert[SERIALIZED_ALERT_SIZE];

#endif //MIGRATION_OFFICE_ALERTDATA_H
