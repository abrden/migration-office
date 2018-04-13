#ifndef MIGRATION_OFFICE_EXCLUSIVELOCK_H
#define MIGRATION_OFFICE_EXCLUSIVELOCK_H

#include "Lock.h"

#include <fcntl.h>
#include <string>

class ExclusiveLock : public Lock {

    public:
        explicit ExclusiveLock(const std::string& name);
        int lock() override;

};

#endif //MIGRATION_OFFICE_EXCLUSIVELOCK_H
