#pragma once 
#include <statistics.hpp>
#include <actor.hpp>
class AtbBattleSystem {
private:
    std::vector<Actor> combatants;
    const float ATB_THRESHOLD = 100.0f; // Max capacity of the action bar
    const float SPEED_MULTIPLIER = 0.5f; // Scales down values for manageable progression

public:
    void add_combatant(Actor actor) ;
    // Runs continuously during combat
    void update(float delta_time);

private:
    void execute_turn(Actor& actor);
};
