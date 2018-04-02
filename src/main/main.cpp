#include <iostream>
#include <fstream>
#include <sstream>
#include <list>

std::list<std::string> init_fugitives_list() {
    std::ifstream ifs("../resources/fugitives.txt");
    std::list<std::string> fugitives_list;
    std::string fugitive_id;

    while (getline(ifs, fugitive_id)) {
        fugitives_list.emplace_back(fugitive_id);
    }
    return fugitives_list;
}


int main(int argc, char* argv[]) {
    std::cout << "Hello, World! This is the Conculandia Migration Office." << std::endl;
    return 0;
}