#include <atbsystem.hpp>

    void AtbBattleSystem::add_combatant(Actor actor) {
        combatants.push_back(actor);
    }

    // Runs continuously during combat
    void AtbBattleSystem::update(float delta_time) {
        for (auto& actor : combatants) {
            if (actor.stats.current_hp <= 0 || actor.is_ready) continue;

            // Fill the ATB bar based on individual Speed and elapsed time
            actor.atb_gauge += actor.spd * delta_time * SPEED_MULTIPLIER;

            // Check if the actor can take a turn
            if (actor.atb_gauge >= ATB_THRESHOLD) {
                actor.atb_gauge = ATB_THRESHOLD;
                actor.is_ready = true;
                execute_turn(actor);
            }
        }
    }


    void AtbBattleSystem::execute_turn(Actor& actor) {
        std::cout << "[ATB READY] " << actor.name << " takes action!\n";
        
        // --- Execute Battle logic / AI decisions / Player input here ---
        
        // Reset ATB state after action resolves
        actor.atb_gauge = 0.0f;
        actor.is_ready = false;
    }