#pragma once

#include <algorithm>
#include <random>
#include <cmath>
#include <statistics.hpp>

class DamageEngine {
private:
    // Thread-safe random number generator for evasion and crit checks
    static float random_percentage() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_real_distribution<float> dis(0.0f, 100.0f);
        return dis(gen);
    }

public:
    struct DamageResult {
        int final_damage = 0;
        bool is_hit = true;
        bool is_crit = false;
    };

    // Computes physical attack vs physical defense
    static DamageResult calculate_physical_damage(const Statistics& attacker, const Statistics& target) {
        DamageResult result;

        // 1. Accuracy vs Evasion Check
        // Base 90% hit rate, modified by attacker's accuracy and target's evasion
        float hit_chance = 90.0f + (attacker.acc - target.eva);
        hit_chance = std::clamp(hit_chance, 5.0f, 100.0f); // Cap between 5% and 100%

        if (random_percentage() > hit_chance) {
            result.is_hit = false;
            result.final_damage = 0;
            return result;
        }

        // 2. Base Damage Calculation (Atk vs Def)
        // Standard RPG Formula: Base = Atk - (Def / 2)
        // Your implicit conversion operator allows us to treat these like integers cleanly
        int base_damage = attacker.atk - (target.def / 2);
        if (base_damage < 1) base_damage = 1; // Guarantee at least 1 raw damage

        // 3. Critical Hit Check
        float crit_chance = static_cast<float>(attacker.crit); 
        if (random_percentage() <= crit_chance) {
            result.is_crit = true;
            // CritDmg modifier (e.g., if crit_dmg value is 150, it means 150% damage)
            float crit_multiplier = attacker.crit_dmg > 0 ? (attacker.crit_dmg / 100.0f) : 1.5f;
            base_damage = static_cast<int>(base_damage * crit_multiplier);
        }

        // 4. Damage Reduction Mitigation (DR%)
        // If target has 15 DR, they take 85% of incoming damage
        float dr_factor = 1.0f - (target.dr / 100.0f);
        dr_factor = std::clamp(dr_factor, 0.0f, 1.0f); // Don't let DR increase damage or heal

        result.final_damage = static_cast<int>(base_damage * dr_factor);
        return result;
    }
};
