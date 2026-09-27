#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

// Include your standalone header files here
#include "statistics.hpp"
#include "combatant.hpp"
#include "damageengine.hpp"
#include "atbsystem.hpp"
#include "priorityqueue.hpp"

// Simple helper to print the status of the battlefield
void print_battlefield_status(const std::vector<Combatant>& party, const std::vector<Combatant>& enemies) {
    std::cout << "\n================= BATTLE GAUGE STATUS =================\n";
    for (const auto& player : party) {
        std::cout << " [Player] " << player.name 
                  << " -> HP: " << player.stats.current_hp.value << "/" << player.stats.max_hp.value
                  << " | ATB: " << player.stats.atb_gauge << "%" 
                  << (player.stats.is_ready ? " [READY]" : "") << "\n";
    }
    for (const auto& enemy : enemies) {
        std::cout << " [Enemy]  " << enemy.name 
                  << " -> HP: " << enemy.stats.current_hp.value << "/" << enemy.stats.max_hp.value
                  << " | ATB: " << enemy.stats.atb_gauge << "%" 
                  << (enemy.stats.is_ready ? " [READY]" : "") << "\n";
    }
    std::cout << "=======================================================\n";
}

int main() {
    std::cout << "Initializing Active Time Battle System Integration Test...\n\n";

    // 1. Initialize Player Party
    std::vector<Combatant> party;
    
    Combatant rogue{"Tifa (Rogue)", {}, true};
    rogue.stats.max_hp = stat::HP{180};
    rogue.stats.current_hp = stat::HP{180};
    rogue.stats.spd = stat::Spd{65};       // Fast!
    rogue.stats.atk = stat::Atk{45};
    rogue.stats.acc = stat::Acc{20};
    rogue.stats.crit = stat::Crit{30};     // 30% Crit Rate
    rogue.stats.crit_dmg = stat::CritDmg{180}; // 180% Damage on crit
    party.push_back(rogue);

    Combatant warrior{"Barret (Tank)", {}, true};
    warrior.stats.max_hp = stat::HP{320};
    warrior.stats.current_hp = stat::HP{320};
    warrior.stats.spd = stat::Spd{25};     // Slow but sturdy
    warrior.stats.atk = stat::Atk{55};
    warrior.stats.def = stat::Def{40};
    warrior.stats.dr = stat::DR{15};       // 15% flat damage reduction
    party.push_back(warrior);

    // 2. Initialize Enemies
    std::vector<Combatant> enemies;

    Combatant boss{"Guard Scorpion", {}, true};
    boss.stats.max_hp = stat::HP{600};
    boss.stats.current_hp = stat::HP{600};
    boss.stats.spd = stat::Spd{32};        // Moderate speed
    boss.stats.atk = stat::Atk{60};
    boss.stats.def = stat::Def{30};
    boss.stats.dr = stat::DR{10};
    enemies.push_back(boss);

    // 3. Initialize Battle Engine Helpers
    ActionQueueManager queue_manager;

    // Use a relatively large simulated delta time to force simultaneous cross-overs 
    // and showcase how your priority queue breaks ties gracefully!
    float simulated_dt = 1.2f; 
    int current_turn_cycle = 1;

    // Run the loop until either the players die or the boss dies
    while (boss.is_alive && (party[0].is_alive || party[1].is_alive)) {
        
        // Step A: Check if anyone is ready to act. If not, tick the clock.
        bool actions_available = false;
        for (const auto& p : party)   if (p.stats.is_ready) actions_available = true;
        for (const auto& e : enemies) if (e.stats.is_ready) actions_available = true;

        if (!actions_available) {
            std::cout << "\nTicking clock by delta time " << simulated_dt << "s...\n";
            AtbEngine::tick_battle_clock(party, enemies, simulated_dt);
            print_battlefield_status(party, enemies);
            continue;
        }

        // Step B: Populating the Action Priority Queue if nodes are ready
        std::cout << "\n[BATTLE ENGINE] Halting clock. Extracting actions into priority queue...\n";
        queue_manager.populate_queue(party, enemies);

        // Step C: Process the action sequence back-to-back while the clock remains frozen
        while (queue_manager.has_actions_pending()) {
            Combatant* current_actor = queue_manager.pop_next_actor();
            
            // Safety fallback if they were defeated in the exact same turn queue window
            if (!current_actor || !current_actor->is_alive) continue; 

            std::cout << "\n-------------------------------------------------------\n";
            std::cout << ">>> TURN #" << current_turn_cycle++ << ": [" << current_actor->name << "] takes action!\n";

            // Establish targets dynamically
            Combatant* target = nullptr;
            if (current_actor->name.find("Guard Scorpion") != std::string::npos) {
                // Boss picks a random living party member (simplification)
                target = party[0].is_alive ? &party[0] : &party[1];
            } else {
                // Players always target the boss
                target = &boss;
            }

            std::cout << "-> " << current_actor->name << " targets " << target->name << "\n";

            // Run structural Damage calculations!
            DamageEngine::DamageResult battle_hit = DamageEngine::calculate_physical_damage(current_actor->stats, target->stats);

            if (battle_hit.is_hit) {
                stat::HP damage_to_inflict{ static_cast<std::int16_t>(battle_hit.final_damage) };
                target->stats.current_hp -= damage_to_inflict;

                std::cout << "-> Strike LANDED! Dealt " << battle_hit.final_damage << " damage";
                if (battle_hit.is_crit) std::cout << " (CRITICAL HIT! 💥)";
                std::cout << ".\n";

                // Death monitoring
                if (target->stats.current_hp.value <= 0) {
                    target->stats.current_hp = stat::HP{0};
                    target->is_alive = false;
                    std::cout << "☠️  " << target->name << " has been DEFEATED!\n";
                }
            } else {
                std::cout << "-> The attack MISSED! 💨\n";
            }

            // Consume the turn, resetting their metrics
            AtbEngine::consume_turn(*current_actor);
        }
        
        // Clear queue properties cleanly for the next sweep
        queue_manager.clear();
    }

    std::cout << "\n=======================================================\n";
    std::cout << "COMBAT CONCLUDED. ";
    if (!boss.is_alive) {
        std::cout << "VICTORY! The players successfully defeated the Guard Scorpion!\n";
    } else {
        std::cout << "GAME OVER. The party was wiped out.\n";
    }
    std::cout << "=======================================================\n";

    return 0;
}
