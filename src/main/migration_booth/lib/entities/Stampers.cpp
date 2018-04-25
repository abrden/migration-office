#include <src/main/common/definitions/FileNames.h>
#include "Stampers.h"


Stampers::Stampers(const int stampers_number) : stampers(StampersSemaphore::SEM_FILE, StampersSemaphore::LETTER, stampers_number) {}

void Stampers::get_stamper() {
    stampers.p();
}

void Stampers::return_stamper() {
    stampers.v();
}

Stampers::~Stampers() {
    stampers.destroy();
}