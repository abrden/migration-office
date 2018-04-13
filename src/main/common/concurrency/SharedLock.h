#ifndef MIGRATION_OFFICE_SHAREDLOCK_H
#define MIGRATION_OFFICE_SHAREDLOCK_H

#include "Lock.h"

#include <fcntl.h>
#include <string>

class SharedLock : public Lock {

    public:
        explicit SharedLock(const std::string& name);
        int lock() override;
};


#endif //MIGRATION_OFFICE_SHAREDLOCK_H
