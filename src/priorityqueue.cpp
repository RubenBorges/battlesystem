#pragma once
#include <combatant.hpp>
#include <priorityqueue.hpp>
#include <queue>
#include <statistics.hpp>
#include <vector>

void ActionQueueManager::populate_queue(std::vector<Combatant> &party,
                                        std::vector<Combatant> &enemies) {
  const float MAX_GAUGE = 100.0f;

  for (auto &actor : party) {
    if (actor.is_alive && actor.stats.is_ready) {
      float overflow = actor.stats.atb_gauge - MAX_GAUGE;
      active_queue.push({&actor, overflow});
    }
  }

  for (auto &enemy : enemies) {
    if (enemy.is_alive && enemy.stats.is_ready) {
      float overflow = enemy.stats.atb_gauge - MAX_GAUGE;
      active_queue.push({&enemy, overflow});
    }
  }
}

bool ActionQueueManager::has_actions_pending() const {
  return !active_queue.empty();
}

Combatant *ActionQueueManager::pop_next_actor() {
  if (active_queue.empty())
    return nullptr;

  Combatant *next_up = active_queue.top().actor;
  active_queue.pop();
  return next_up;
}

void ActionQueueManager::clear() {
  while (!active_queue.empty())
    active_queue.pop();
}
