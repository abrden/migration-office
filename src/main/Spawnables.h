#ifndef MIGRATION_OFFICE_SPAWNEABLE_H
#define MIGRATION_OFFICE_SPAWNEABLE_H

#include "Spawnable.h"

#include <utility>
#include <list>

class Spawnables {

    protected:
        std::list<std::pair<int, Spawnable*>> items;

    public:
        typedef std::list<std::pair<int, Spawnable*>>::iterator iterator;
        Spawnables::iterator begin();
        Spawnables::iterator end();
        Spawnables::iterator erase(Spawnables::iterator iterator);
        void sort_by_ascending_timestamp();
        bool empty();
        std::list<std::pair<int, Spawnable*>>& get_items();
        virtual ~Spawnables();

};

#endif //MIGRATION_OFFICE_SPAWNEABLE_H
