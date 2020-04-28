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
        (size_t) floor(((double) i) / 2.0) // team_; Will give 0 for the first two players_ and 1 for the two remaining ones.
    };
    players_.push_back(player);
  }
  //TODO add name validation to prevent players from entering same name
}

GameEngine::~GameEngine() {
  for (const auto& player : players_) {
    delete player.strategy_ptr_;
  }
}

void GameEngine::RunGame() {

}

void GameEngine::CommunicateNames() {
  for (const auto& current_player_ : players_) {
    string teammate_name_;
    vector<string> opponent_names_;

    for (const auto& other_player_ :players_) {
      if (current_player_ == other_player_) {
        continue;
      } else if (current_player_.team_ == other_player_.team_) {
        teammate_name_ = other_player_.name_;
      } else {
        opponent_names_.push_back(other_player_.name_);
      }
    }

    current_player_.strategy_ptr_->receiveNames(teammate_name_, opponent_names_);
  }
}
void GameEngine::DealCards(Deck deck_) {
  for (const auto& player_ : players_) {
    vector<Card> cards_to_deal_;
    for (size_t i = 0; i < kNumCardsPerPlayer; i++) {
      cards_to_deal_.push_back(deck_.Draw());
    }
    player_.strategy_ptr_->receiveInitialCards(cards_to_deal_);
  }
}

}