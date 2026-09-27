#pragma once
#include <statistics.hpp>
#include <string>

struct Combatant {
    std::string name;
    Statistics stats;
    bool is_alive = true;
};
