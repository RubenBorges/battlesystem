#pragma once
#include <cstdint>
#include <statistics.hpp>
#include <string>

class Actor{
    std::string name;
    stat::HP max_hp;
    stat::HP current_hp;
    stat::Spd spd;            // Higher speed = ATB bar fills faster
    
    float atb_gauge = 0.0f;   // Ranges from 0.0 to 1.0 (100%)
    bool is_ready = false;
};