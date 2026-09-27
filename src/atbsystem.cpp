#include <atbsystem.hpp>
#include <iostream>
#include <algorithm>

// Core tick function executed once per frame in your main game loop
void AtbEngine::tick_battle_clock(std::vector<Combatant>& party, std::vector<Combatant>& enemies, float delta_time) {
        
        // 1. Process the Player Party
        for (auto& actor : party) {
            if (!actor.is_alive || actor.stats.is_ready) continue;

            // Advance gauge using implicit cast conversion for spd
            float speed_modifier = static_cast<float>(actor.stats.spd);
            actor.stats.atb_gauge += speed_modifier * delta_time * TIME_SCALE_FACTOR;

            // Handle Action Threshold
            if (actor.stats.atb_gauge >= MAX_GAUGE) {
                actor.stats.atb_gauge = MAX_GAUGE;
                actor.stats.is_ready = true;
                std::cout << "[ATB READY] " << actor.name << " (Player) is ready to act!\n";
            }
        }

        // 2. Process Enemy Encounters
        for (auto& enemy : enemies) {
            if (!enemy.is_alive || enemy.stats.is_ready) continue;

            float speed_modifier = static_cast<float>(enemy.stats.spd);
            enemy.stats.atb_gauge += speed_modifier * delta_time * TIME_SCALE_FACTOR;

            if (enemy.stats.atb_gauge >= MAX_GAUGE) {
                enemy.stats.atb_gauge = MAX_GAUGE;
                enemy.stats.is_ready = true;
                std::cout << "[ATB READY] " << enemy.name << " (Enemy) preparing action...\n";
            }
        }
    }

    // Call this immediately after an action (attack, item, spell) successfully finishes resolving
void AtbEngine::consume_turn(Combatant& actor) {
        actor.stats.atb_gauge = 0.0f;
        actor.stats.is_ready = false;
        std::cout << "[ATB RESET] " << actor.name << "'s action gauge has been cleared.\n";
    }

