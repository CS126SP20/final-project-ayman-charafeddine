//
// Created by ayman on 4/26/20.
//

#ifndef FINALPROJECT_INCLUDE_LIKHA_GAMEENGINE_H_
#define FINALPROJECT_INCLUDE_LIKHA_GAMEENGINE_H_

#include "Card.h"
#include "Deck.h"
#include "PlayerStartegy.h"
#include <vector>
#include <string>

using namespace likha;
using std::vector;
using std::string;

static constexpr size_t kNumPlayers = 4;

class GameEngine {
 public:
  /**
   *
   * @param playerStrategies_ vector of PlayerStrategies. Any PlayerStrategy after the 4th will be ignored.
   */
  GameEngine(const vector<PlayerStrategy>& playerStrategies_);

 private:
  struct Player {
    PlayerStrategy& strategy_;
    string name_;
    size_t score_;
    size_t team_;
  };

  vector<Player> players;

};

#endif //FINALPROJECT_INCLUDE_LIKHA_GAMEENGINE_H_
