#include "../include/Route.hpp"
#include <utility>

Route::Route(std::string name, double distance)
    : name(std::move(name)), distance(distance) {
}
