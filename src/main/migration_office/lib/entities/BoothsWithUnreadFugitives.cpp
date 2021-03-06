#include "FileNames.h"
#include "BoothsWithUnreadFugitives.h"

BoothsWithUnreadFugitives::BoothsWithUnreadFugitives(const int booths_number) : booths(FugitivesFifo::SEM_FILE, FugitivesFifo::LETTER) {
    booths.init(booths_number);
}

BoothsWithUnreadFugitives::~BoothsWithUnreadFugitives() {
    booths.destroy();
}
