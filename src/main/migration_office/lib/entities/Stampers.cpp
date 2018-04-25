#include "FileNames.h"
#include "Stampers.h"


Stampers::Stampers(const int stampers_number) : stampers(StampersSemaphore::SEM_FILE, StampersSemaphore::LETTER) {
    stampers.init(stampers_number);
}

Stampers::~Stampers() = default;