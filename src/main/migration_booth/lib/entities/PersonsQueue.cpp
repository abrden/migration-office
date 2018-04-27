#include <iostream>
#include "Foreigner.h"
#include "PersonDeserializer.h"
#include "PersonsQueue.h"

static const std::string FIFO_FILE = "/tmp/spawnerfifo";
static const std::string FIFO_LOCK_FILE = "/tmp/spawnerfifolock";
static const int BUFF_SIZE = 1024;

enum ERRORS {
    BUFFER_EXCEEDED = -1
};

PersonsQueue::PersonsQueue(Logger& logger) : logger(logger), fifo(FIFO_FILE), fifo_lock(FIFO_LOCK_FILE) {}

Person* PersonsQueue::front() {
    fifo_lock.lock();
    unsigned long buffer_size;
    logger(BOOTH_QUEUE) << "Trying to read size" << std::endl;
    ssize_t bytes_read = fifo.fifo_read(static_cast<void*>(&buffer_size), sizeof(unsigned long));
    if (bytes_read != sizeof(unsigned long)) {
        logger(BOOTH_QUEUE) << "I couldnt read ulong. I read this many bytes: " << bytes_read << std::endl;
        return nullptr;
    }
    logger(BOOTH_QUEUE) << "I read size: " << buffer_size << std::endl;

    if (buffer_size > BUFF_SIZE) {
        throw std::system_error(ERRORS::BUFFER_EXCEEDED, std::generic_category(), "Serialized person buffer exceeded.");
    }
    char buffer[BUFF_SIZE]; //TODO raise exception if size exceeds BUFF_SIZE
    logger(BOOTH_QUEUE) << "Trying to read serialized person" << std::endl;
    bytes_read = fifo.fifo_read(static_cast<void*>(buffer), sizeof(char) * buffer_size);
    if ((unsigned long) bytes_read != buffer_size) {
        logger(BOOTH_QUEUE) << "I couldnt read a person. I read this many bytes: " << bytes_read << std::endl;
        return nullptr;
    }
    fifo_lock.unlock();

    std::string serialized_person(buffer, buffer_size);
    logger(BOOTH_QUEUE) << "I read person: " << serialized_person << std::endl;

    return PersonDeserializer::deserialize(serialized_person);
}