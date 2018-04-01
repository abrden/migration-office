#ifndef MIGRATION_OFFICE_SPAWNER_H
#define MIGRATION_OFFICE_SPAWNER_H

#include <list>
#include <utility>

template <class T>
class Spawner {

    private:
        std::list<std::pair<int, T*>>& items;

    public:
        explicit Spawner(std::list<std::pair<int, T*>>& items);
        void run();
        ~Spawner();

};


#endif //MIGRATION_OFFICE_SPAWNER_H
