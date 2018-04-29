#include <src/main/common/definitions/FileNames.h>
#include "BoothsWithUnreadFugitives.h"

BoothsWithUnreadFugitives::BoothsWithUnreadFugitives() : booths(FugitivesFifo::SEM_FILE, FugitivesFifo::LETTER) {}

void BoothsWithUnreadFugitives::wait_for_booths_to_read() {
    booths.w();
}