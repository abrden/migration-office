#include "Alerts.h"

void Alerts::push_alert(int timestamp, WantedPersonAlert* alert) {
    items.emplace_back(std::make_pair(timestamp,alert));
}

Alerts::~Alerts() {}