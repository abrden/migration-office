#include "Foreigner.h"
#include "PersonDeserializer.h"
#include "PersonsQueue.h"
#include "Resident.h"

const static std::string fifo_file = "/tmp/spawner_fifo";
const static int BUFF_SIZE = 1024;

PersonsQueue::PersonsQueue() : fifo(fifo_file) {}

bool PersonsQueue::empty() {
    // TODO
    return false;
}

Person* PersonsQueue::front() {
    int buffer_size;
    fifo.fifo_read(&buffer_size, sizeof(int));

    char buffer[BUFF_SIZE]; //TODO raise exception if size exceeds BUFF_SIZE
    fifo.fifo_read(buffer, sizeof(char) * buffer_size);

    std::string serialized_person(buffer, buffer_size);

    //return PersonDeserializer::deserialize(serialized_person);

    std::list<Feature*> l;
    return new Resident(13641107, l);
}