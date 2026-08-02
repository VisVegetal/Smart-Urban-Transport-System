#ifndef PERSISTENCE_HPP
#define PERSISTENCE_HPP

#include <string>
#include "Dispatcher.hpp"

class Persistence {
public:
    static void saveSystem(const Dispatcher& d, const std::string& fileName);

    static void loadSystem(Dispatcher& d, const std::string& fileName);

    static bool isFileValid(const std::string& fileName);
};

#endif
