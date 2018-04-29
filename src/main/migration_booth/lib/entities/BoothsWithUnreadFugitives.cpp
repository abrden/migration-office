#include <src/main/common/definitions/FileNames.h>
#include "BoothsWithUnreadFugitives.h"

BoothsWithUnreadFugitives::BoothsWithUnreadFugitives() : booths(FugitivesFifo::SEM_FILE, FugitivesFifo::LETTER) {}

void BoothsWithUnreadFugitives::notify_read_fugitives() {
    booths.p();
}