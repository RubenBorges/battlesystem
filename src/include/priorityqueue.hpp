#pragma once
#include <combatant.hpp>
#include <compare>
#include <queue>
#include <statistics.hpp>
#include <vector>

class ActionQueueManager {
public:
  struct TurnRequest {
    Combatant *actor;
    float overflow_gauge;

    friend std::partial_ordering operator<=>(const TurnRequest &lhs,
                                             const TurnRequest &rhs) noexcept {
      if (auto cmp = lhs.overflow_gauge <=> rhs.overflow_gauge; cmp != 0) {
        return cmp; // This returns std::partial_ordering
      }
      // This returns std::strong_ordering, but safely converts to
      // std::partial_ordering
      return lhs.actor->stats.spd <=> rhs.actor->stats.spd;
    }

    friend bool operator<(const TurnRequest &lhs,
                          const TurnRequest &rhs) noexcept {
      return (lhs <=> rhs) < 0;
    }
  };

  void populate_queue(std::vector<Combatant> &party,
                      std::vector<Combatant> &enemies);
  bool has_actions_pending() const;
  Combatant *pop_next_actor();
  void clear();

private:
  std::priority_queue<TurnRequest> active_queue;
};
