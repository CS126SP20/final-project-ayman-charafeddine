//
// Created by ayman on 4/26/20.
//

#include <likha/GameEngine.h>
#include <math.h>

GameEngine::GameEngine(const vector<PlayerStrategy>& playerStrategies_ ) {
  for (size_t i = 0; i < kNumPlayers; i++) {
    Player player = {
        &playerStrategies_[i], // strategy_
        playerStrategies_[i].chooseName(), // name_
        0, // score_
        (size_t) floor(((double) i) / 2.0) // team_ Will give 0 for the first two players and 1 for the two remaining ones.
    };
  }
}

