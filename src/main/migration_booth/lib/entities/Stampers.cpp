#include "FileNames.h"
#include "Stampers.h"


Stampers::Stampers() : stampers(StampersSemaphore::SEM_FILE, StampersSemaphore::LETTER) {}

void Stampers::get_stamper() {
    stampers.p();
}

void Stampers::return_stamper() {
    stampers.v();
}