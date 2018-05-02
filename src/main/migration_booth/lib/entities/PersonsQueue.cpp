#include <iostream>
#include <stdexcept>

#include "Foreigner.h"
#include "PersonDeserializer.h"
#include "PersonsQueue.h"
#include "FileNames.h"

static const int BUFF_SIZE = 1024;

PersonsQueue::PersonsQueue(Logger& logger) : logger(logger), fifo(PeopleFifo::FIFO_FILE), fifo_lock(PeopleFifo::BOOTH_LOCK_FILE) {}

Person* PersonsQueue::front() {
    fifo_lock.lock();
    unsigned long buffer_size;
    ssize_t bytes_read = fifo.fifo_read(static_cast<void*>(&buffer_size), sizeof(unsigned long));
    if (bytes_read == 0) {
        logger(BOOTH_QUEUE) << "No more persons on the queue" << std::endl;
        fifo_lock.unlock();
        return nullptr;
    } else if ((unsigned long) bytes_read < sizeof(unsigned long)) {
        fifo_lock.unlock();
        throw std::runtime_error("I couldnt read person size ulong. I read this many bytes: " + bytes_read);
    }

    if (buffer_size > BUFF_SIZE) {
        fifo_lock.unlock();
        throw std::overflow_error("Serialized person buffer exceeded.");
    }
    char buffer[BUFF_SIZE];

    bytes_read = fifo.fifo_read(static_cast<void*>(buffer), sizeof(char) * buffer_size);
    if (bytes_read == 0) {
        logger(BOOTH_QUEUE) << "No more persons to on the queue" << std::endl;
    } else if ((unsigned long) bytes_read < buffer_size) {
        fifo_lock.unlock();
        throw std::runtime_error("I couldnt read a person. I read this many bytes: " + bytes_read);
    }
    fifo_lock.unlock();

    std::string serialized_person(buffer, buffer_size);
    logger(BOOTH_QUEUE) << "I received person: " << serialized_person << ". with size: " << buffer_size << std::endl;

    return PersonDeserializer::deserialize(serialized_person);
}