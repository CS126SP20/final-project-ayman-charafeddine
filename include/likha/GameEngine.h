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

using std::vector;
using std::string;

namespace likha {

static constexpr size_t kNumPlayers = 4;

class GameEngine {
 private:
  struct Player {
    PlayerStrategy* strategy_ptr_;
    string name_;
    size_t score_;
    size_t team_;
  };

 public:
  /**
   *
   * @param playerStrategies_ vector of PlayerStrategies. Any PlayerStrategy after the 4th will be ignored.
   */
  GameEngine(vector<PlayerStrategy*> playerStrategies_);

  ~GameEngine();
  vector<Player> players;
};

}

#endif //FINALPROJECT_INCLUDE_LIKHA_GAMEENGINE_H_
