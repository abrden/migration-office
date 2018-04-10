#include "PersonsQueue.h"
#include "Resident.h"

bool PersonsQueue::empty() {
    // TODO
    return false;
}

Person* PersonsQueue::front() {
    // TODO
    std::list<Feature*> features;
    features.emplace_back(new Feature("redish hair"));
    features.emplace_back(new Feature("green eyes"));
    return new Resident(13641107, features);
}