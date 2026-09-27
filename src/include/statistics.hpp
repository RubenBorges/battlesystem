
#include <cstdint>
#include <iostream>
#include <vector>
#include <string>

namespace stat{
//Core Statistics
struct HP       { std::int16_t value; }; //Health / Hit Points (HP)
struct MP       { std::int16_t value; }; //Mana / Skill Points (MP / SP)
struct Atk      { std::int16_t value; }; //Physical Attack (ATK / STR)
struct Def      { std::int16_t value; }; //Physical Defense (DEF / VIT)
struct Int     { std::int16_t value; }; //Magic Attack (MATK / INT)
struct Spirit     { std::int16_t value; }; //Magic Defense (MDEF / SPR)
 
//Turn & Action Modifiers //
struct Spd      { std::int16_t value; }; //Speed / Agility (SPD / AGI):
struct Crit     { std::int16_t value; }; //Critical Hit Rate (CRT%)
struct CritDmg  { std::int16_t value; }; //Critical Damage Multiplier (CRIT DMG)
struct Acc      { std::int16_t value; }; //Accuracy / Hit Rate (ACC)
struct Eva      { std::int16_t value; }; //Evasion / Dodge (EVA)
 
// Defensive & Mitigation Modifiers //
struct Block    { std::int16_t value; }; //Block Rate / Parry
struct DR       { std::int16_t value; }; //Damage Reduction (DR%)
struct VAMP     { std::int16_t value; }; //Lifesteal / Omnivamp (VAMP%)
struct Resist   { std::int16_t value; }; //Tenacity / Resistance
 
//Attribute & Progression Modifiers //
struct Aggro    { std::int16_t value; }; //Aggro / Threat Rate:
struct Affinity { std::int16_t value; }; //Elemental Mastery / Affinity
struct CDR      { std::int16_t value; }; //Cooldown Reduction (CDR)
struct XpMod    { std::int16_t value; }; //Experience Modifier (EXP%)
} //namespace stat


class Statistics{

};