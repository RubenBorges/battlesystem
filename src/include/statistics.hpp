#pragma once 
#include <compare>
#include <cstdint>

namespace stat {

    // Helper CRTP Mixin to automatically inject operators safely into your types
template <typename Derived>
struct Arithmetic {
    constexpr Arithmetic() noexcept = default;
    constexpr Arithmetic(std::int16_t val) noexcept {
        static_cast<Derived*>(this)->value = val;
    }

    // --- Automatic Type-Safe Spaceship & Equality Operators ---
    constexpr friend auto operator<=>(const Derived& lhs, const Derived& rhs) noexcept {
        return lhs.value <=> rhs.value;
    }
    constexpr friend bool operator==(const Derived& lhs, const Derived& rhs) noexcept {
        return lhs.value == rhs.value;
    }

    // --- Compound Assignments ---
    constexpr Derived& operator+=(const Derived& rhs) noexcept {
        static_cast<Derived*>(this)->value += rhs.value;
        return *static_cast<Derived*>(this);
    }
    constexpr Derived& operator-=(const Derived& rhs) noexcept {
        static_cast<Derived*>(this)->value -= rhs.value;
        return *static_cast<Derived*>(this);
    }
    
    // --- Scaling Assignments ---
    constexpr Derived& operator*=(std::int16_t scalar) noexcept {
        static_cast<Derived*>(this)->value *= scalar;
        return *static_cast<Derived*>(this);
    }
    constexpr Derived& operator/=(std::int16_t scalar) noexcept {
        static_cast<Derived*>(this)->value /= scalar;
        return *static_cast<Derived*>(this);
    }

    // --- Binary Operators ---
    constexpr friend Derived operator+(Derived lhs, const Derived& rhs) noexcept { lhs += rhs; return lhs; }
    constexpr friend Derived operator-(Derived lhs, const Derived& rhs) noexcept { lhs -= rhs; return lhs; }
    constexpr friend Derived operator*(Derived lhs, std::int16_t scalar) noexcept { lhs *= scalar; return lhs; }
    constexpr friend Derived operator*(std::int16_t scalar, Derived rhs) noexcept { rhs *= scalar; return rhs; }
    constexpr friend Derived operator/(Derived lhs, std::int16_t scalar) noexcept { lhs /= scalar; return lhs; }

    // --- Implicit Conversion ---
    constexpr operator std::int16_t() const noexcept { return static_cast<const Derived*>(this)->value; }
};

    //=================//
    // Core Statistics //
    //=================//
    struct HP : Arithmetic<HP>         {std::int16_t value{0};};
    struct MP : Arithmetic<MP>         {std::int16_t value{0};};
    struct Atk : Arithmetic<Atk>       {std::int16_t value{0};};
    struct Def : Arithmetic<Def>       {std::int16_t value{0};};
    struct Int : Arithmetic<Int>       {std::int16_t value{0};};
    struct Spirit : Arithmetic<Spirit> {std::int16_t value{0};};

    //==========================//
    // Turn & Action Modifiers //
    //=========================//
    struct Spd : Arithmetic<Spd>         {std::int16_t value{0};};
    struct Crit : Arithmetic<Crit>       {std::int16_t value{0};};
    struct CritDmg : Arithmetic<CritDmg> {std::int16_t value{0};};
    struct Acc : Arithmetic<Acc>         {std::int16_t value{0};};
    struct Eva : Arithmetic<Eva>         {std::int16_t value{0};};

    //==================================//
    // Defensive & Mitigation Modifiers //
    //==================================//
    struct Block : Arithmetic<Block>   {std::int16_t value{0};};
    struct DR : Arithmetic<DR>         {std::int16_t value{0};};
    struct VAMP : Arithmetic<VAMP>     {std::int16_t value{0};};
    struct Resist : Arithmetic<Resist> {std::int16_t value{0};};

    //===================================//
    // Attribute & Progression Modifiers //
    //===================================//
    struct Aggro : Arithmetic<Aggro>       {std::int16_t value{0};};
    struct Affinity : Arithmetic<Affinity> {std::int16_t value{0};};

    // Cooldown Reduction (CDR)
    struct CDR : Arithmetic<CDR>     {std::int16_t value{0};};
    struct XpMod : Arithmetic<XpMod> {std::int16_t value{0};};
} // namespace stat

struct Statistics {
    stat::HP     current_hp{0};
    stat::MP     current_mp{0};
    stat::HP         max_hp{0};
    stat::MP         max_mp{0};
    stat::Atk           atk{0};
    stat::Def           def{0};
    stat::Int         intel{0}; 
    stat::Spirit     spirit{0};

    stat::Spd             spd{0};
    float        atb_gauge{0.0f}; 
    bool         is_ready{false};

    stat::Crit          crit{0};
    stat::CritDmg   crit_dmg{0};
    stat::Acc            acc{0};
    stat::Eva            eva{0};

    stat::Block   block{0};
    stat::DR         dr{0};
    stat::VAMP     vamp{0};
    stat::Resist resist{0};

    stat::Aggro       aggro{0};
    stat::Affinity affinity{0};
    stat::CDR           cdr{0};
    stat::XpMod      xp_mod{0};
};
