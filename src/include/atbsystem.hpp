#pragma once 
#include <statistics.hpp>
#include <vector>
#include <string>


struct Combatant {
    std::string name;
    Statistics stats;
    bool is_alive = true;
};

class AtbEngine {
private:
    // Constants controlling the scale and flow of the battle clock
    static constexpr float MAX_GAUGE = 100.0f;
    
    // A global dial to tune how fast combat fields fill across your game
    static constexpr float TIME_SCALE_FACTOR = 0.5f; 

public:
    // Core tick function executed once per frame in your main game loop
    static void tick_battle_clock(std::vector<Combatant>& party, std::vector<Combatant>& enemies, float delta_time) ;

    // Call this immediately after an action (attack, item, spell) successfully finishes resolving
    static void consume_turn(Combatant& actor) ;
};
