//
// Created by ayman on 4/26/20.
//

#include <likha/GameEngine.h>
#include <cmath>

namespace likha {

GameEngine::GameEngine(vector<PlayerStrategy*> playerStrategies_) {
  for (size_t i = 0; i < kNumPlayers; i++) {
    PlayerStrategy* strategy = playerStrategies_[i];
    Player player = {
         strategy, // strategy_ptr_
        playerStrategies_[i]->chooseName(), // name_
        0, // score_
        (size_t) floor(((double) i) / 2.0) // team_; Will give 0 for the first two players and 1 for the two remaining ones.
    };
    players.push_back(player);
  }
}
GameEngine::~GameEngine() {
  for (const auto& player : players) {
    delete player.strategy_ptr_;
}
}

}