#include "Statistics.h"
Statistics::Statistics() {
    residents_allowed = 0;
    residents_detained = 0;
    foreigners_allowed = 0;
    foreigners_deported = 0;
}

size_t Statistics::get_allowed_residents() const {
    return residents_allowed;
}

size_t Statistics::get_detained_residents() const {
    return residents_detained;
}

size_t Statistics::get_allowed_foreigners() const {
    return foreigners_allowed;
}

size_t Statistics::get_deported_foreigners() const {
    return foreigners_deported;
}
