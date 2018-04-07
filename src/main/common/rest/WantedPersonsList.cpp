#include "WantedPersonsList.h"

void WantedPersonsList::add_alert(WantedPersonAlert* alert) {
    list.emplace_back(alert);
}

WantedPersonsList::~WantedPersonsList() {
    while (!list.empty()) {
        delete list.back();
        list.pop_back();
    }
}