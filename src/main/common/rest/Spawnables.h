#ifndef MIGRATION_OFFICE_SPAWNEABLE_H
#define MIGRATION_OFFICE_SPAWNEABLE_H

#include "Spawnable.h"

#include <utility>
#include <list>
#include <string>

class Spawnables {

    private:
        std::list<std::pair<int, std::string>> items;

    public:
        typedef std::list<std::pair<int, std::string>>::iterator iterator;
        Spawnables::iterator begin();
        Spawnables::iterator end();
        Spawnables::iterator erase(Spawnables::iterator iterator);
        void sort_by_ascending_timestamp();
        bool empty();
        void push_spawnable(int timestamp, std::string spawnable);
        std::list<std::pair<int, std::string>>& get_items();
        virtual ~Spawnables();

};

#endif //MIGRATION_OFFICE_SPAWNEABLE_H
