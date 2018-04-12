#include "PersonsQueue.h"
#include "Resident.h"

bool PersonsQueue::empty() {
    // TODO
    return false;
}

Person* PersonsQueue::front() {
    // TODO lock
    Person* person = NULL;
    ssize_t bytes_read = pipe.pipe_read(static_cast<void*>(person), sizeof(Person*));
    if (bytes_read != sizeof(Person*)) {
        // TODO error handling
    }
    // TODO access shared memory
    // TODO unlock

    std::list<Feature*> features;
    features.emplace_back(new Feature("redish hair"));
    features.emplace_back(new Feature("green eyes"));
    return new Resident(13641107, features);
}