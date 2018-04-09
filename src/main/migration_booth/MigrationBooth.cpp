#include <iostream>
#include <src/main/common/entities/Stamper.h>
#include "MigrationBooth.h"

MigrationBooth::MigrationBooth(const std::string people_file, const std::string alerts_file,
                               const std::string fugitives_file,
                               const bool debug, const std::string log_file)
        : people_file(people_file), alerts_file(alerts_file), fugitives_file(fugitives_file),
          debug(debug), log_file(log_file) {}

bool MigrationBooth::queue_empty() {
    // TODO
    return false;
}

Person* MigrationBooth::front() {
    // TODO
    std::list<Feature*> features;
    features.emplace_back(new Feature("redish hair"));
    features.emplace_back(new Feature("green eyes"));
    return new Resident(13641107, features);
}

bool MigrationBooth::is_fugitive(Resident* resident) {
    // TODO
    return false;
}

void MigrationBooth::report_to_police(Resident* resident) {
    // TODO
    std::cout << "Resident " << resident->get_id() << " you are arrested" << std::endl;
}

void MigrationBooth::attend_resident(Resident* resident) {
    if (!is_fugitive(resident)) {
        std::cout << "Welcome to Conculandia, resident " << resident->get_id() << std::endl;
        arrived_residents_ids.emplace_back(resident->get_id());
    } else {
        report_to_police(resident);
    }
}

bool MigrationBooth::is_wanted_person(Foreigner* foreigner) {
    // TODO
    return false;
}

Stamper* MigrationBooth::get_stamper() {
    // TODO
    return new Stamper();
}

void MigrationBooth::attend_foreigner(Foreigner* foreigner) {
    if (is_wanted_person(foreigner)) {
        std::cout << "Foreigner, you are deported" << std::endl;
    } else {
        Stamper* stamper = get_stamper();
        foreigner->get_passport().stamp_passport(*stamper);
        std::cout << "Welcome to Conculandia foreigner" << std::endl;
    }
}

void MigrationBooth::open() {
    while (!queue_empty()) {
        Person* person = front();
        if (person->has_id())
            attend_resident((Resident*)person);
        else
            attend_foreigner((Foreigner*)person);
    }
}