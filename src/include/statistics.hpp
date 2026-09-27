
#include <compare>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
namespace stat {
// Core Statistics

// Health / Hit Points (HP)
struct HP {
  std::int16_t value{0};
  friend auto operator<=>(const HP &lhs, const HP &rhs) = default;
};

// Mana / Skill Points (MP / SP)
struct MP {
  std::int16_t value{0};
  friend auto operator<=>(const MP &lhs, const MP &rhs) = default;
};

// Physical Attack (ATK / STR)
struct Atk {
  std::int16_t value{0};
  friend auto operator<=>(const Atk &lhs, const Atk &rhs) = default;
};

// Physical Defense (DEF / VIT)
struct Def {
  std::int16_t value{0};
  friend auto operator<=>(const Def &lhs, const Def &rhs) = default;
};

// Magic Attack (MATK / INT)
struct Int {
  std::int16_t value{0};
  friend auto operator<=>(const Int &lhs, const Int &rhs) = default;
};

// Magic Defense (MDEF / SPR)
struct Spirit {
  std::int16_t value{0};
  friend auto operator<=>(const Spirit &lhs, const Spirit &rhs) = default;
};

// Turn & Action Modifiers //

// Speed / Agility (SPD / AGI):
struct Spd {
  std::int16_t value{0};
  friend auto operator<=>(const Spd &lhs, const Spd &rhs) = default;
};

// Critical Hit Rate (CRT%)
struct Crit {
  std::int16_t value{0};
  friend auto operator<=>(const Crit &lhs, const Crit &rhs) = default;
};

// Critical Damage Multiplier (CRIT DMG)
struct CritDmg {
  std::int16_t value{0};
  friend auto operator<=>(const CritDmg &lhs, const CritDmg &rhs) = default;
};

// Accuracy / Hit Rate (ACC)
struct Acc {
  std::int16_t value{0};
  friend auto operator<=>(const Acc &lhs, const Acc &rhs) = default;
};

// Evasion / Dodge (EVA)
struct Eva {
  std::int16_t value{0};
  friend auto operator<=>(const Eva &lhs, const Eva &rhs) = default;
};

// Defensive & Mitigation Modifiers //

// Block Rate / Parry
struct Block {
  std::int16_t value{0};
  friend auto operator<=>(const Block &lhs, const Block &rhs) = default;
};

// Damage Reduction (DR%)
struct DR {
  std::int16_t value{0};
  friend auto operator<=>(const DR &lhs, const DR &rhs) = default;
};

// Lifesteal / Omnivamp (VAMP%)
struct VAMP {
  std::int16_t value{0};
  friend auto operator<=>(const VAMP &lhs, const VAMP &rhs) = default;
};

// Tenacity / Resistance
struct Resist {
  std::int16_t value{0};
  friend auto operator<=>(const Resist &lhs, const Resist &rhs) = default;
};

// Attribute & Progression Modifiers //

// Aggro / Threat Rate
struct Aggro {
  std::int16_t value{0};
  friend auto operator<=>(const Aggro &lhs, const Aggro &rhs) = default;
};

// Elemental Mastery / Affinity
struct Affinity {
  std::int16_t value{0};
  friend auto operator<=>(const Affinity &lhs, const Affinity &rhs) = default;
};

// Cooldown Reduction (CDR)
struct CDR {
  std::int16_t value{0};
  friend auto operator<=>(const CDR &lhs, const CDR &rhs) = default;
};

// Experience Modifier (EXP%)
struct XpMod {
  std::int16_t value{0};
  friend auto operator<=>(const XpMod &lhs, const XpMod &rhs) = default;
};
} // namespace stat

class Statistics {};