#include <src/main/common/entities/Foreigner.h>
#include "PersonsQueue.h"
#include "Resident.h"

const static std::string file_path = "/bin/ls";
const static char letter = 'A';

PersonsQueue::PersonsQueue() : queue(file_path, letter) {}

bool PersonsQueue::empty() {
    // TODO
    return false;
}

Person* PersonsQueue::front() {
    person_message message;
    queue.read(PETITION, &message);

    std::list<Feature*> features;
    for (int i = 0; i < message.features_size; i++) {
        std::string feature(message.features[i]);
        features.emplace_back(new Feature(feature));
    }

    if (message.is_resident) {
        return new Resident(message.id, features);
    } else {
        std::string passport_id(message.passport_id);
        return new Foreigner(passport_id, features);
    }
}