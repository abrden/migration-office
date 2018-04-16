#include <iostream>
#include "Foreigner.h"
#include "PersonDeserializer.h"
#include "PersonsQueue.h"

static const std::string fifo_file = "/tmp/spawnerfifo";
static const std::string fifo_lock_file = "/tmp/spawnerfifolock";
static const int BUFF_SIZE = 1024;

PersonsQueue::PersonsQueue() : fifo(fifo_file), fifo_lock(fifo_lock_file) {
    fifo.fifo_open();
}

Person* PersonsQueue::front() {
    fifo_lock.lock();
    unsigned long buffer_size;
    std::cout << "Trying to read size" << std::endl;
    fifo.fifo_read(static_cast<void*>(&buffer_size), sizeof(unsigned long));
    std::cout << "I read " << buffer_size << std::endl;

    char buffer[BUFF_SIZE + 1]; //TODO raise exception if size exceeds BUFF_SIZE
    buffer[BUFF_SIZE] = '\0';
    std::cout << "Trying to read serialized person" << std::endl;
    ssize_t bytes_read = fifo.fifo_read(static_cast<void*>(buffer), sizeof(char) * buffer_size);
    std::cout << "I read " << bytes_read << " bytes" << std::endl;
    fifo_lock.unlock();

    std::string serialized_person(buffer, buffer_size);
    std::cout << "I read " << serialized_person << std::endl;

    return PersonDeserializer::deserialize(serialized_person);
}