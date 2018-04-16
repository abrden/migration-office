#include "Foreigner.h"
#include "PersonDeserializer.h"
#include "PersonsQueue.h"
#include "Resident.h"

const static std::string fifo_file = "./migration_spawner";

PersonsQueue::PersonsQueue() : fifo(fifo_file) {}

bool PersonsQueue::empty() {
    // TODO
    return false;
}

Person* PersonsQueue::front() {
    int buffer_size;
    fifo.fifo_read(&buffer_size, sizeof(int));

    char* buffer = nullptr;
    fifo.fifo_read(buffer, buffer_size);

    std::string serialized_person(buffer);

    return PersonDeserializer::deserialize(serialized_person);
}