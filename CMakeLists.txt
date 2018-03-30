cmake_minimum_required(VERSION 3.9)
project(migration_office)

set(CMAKE_CXX_STANDARD 11)

add_executable(migration_office
        src/main.cpp
        LICENSE
        README.md
        src/Person.cpp src/Person.h src/Feature.cpp src/Feature.h src/Passport.cpp src/Passport.h src/Resident.cpp src/Resident.h src/Foreigner.cpp src/Foreigner.h src/Stamper.cpp src/Stamper.h src/WantedPersonAlert.cpp src/WantedPersonAlert.h src/MinisterOfSecurity.cpp src/MinisterOfSecurity.h)
