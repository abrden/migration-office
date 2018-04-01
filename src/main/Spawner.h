#ifndef MIGRATION_OFFICE_SPAWNER_H
#define MIGRATION_OFFICE_SPAWNER_H

#include "Spawnable.h"

#include <list>
#include <string>
#include <utility>

class Spawner {

    protected:
        std::list<std::pair<int, Spawnable*>> items;

    public:
        explicit Spawner(const std::string& file_path);
        virtual std::list<std::pair<int, Spawnable*>> load_items(const std::string& file_path) = 0;
        void run();
        const std::list<std::pair<int, Spawnable*>>& get_items();
        virtual ~Spawner();

};


#endif //MIGRATION_OFFICE_SPAWNER_H
