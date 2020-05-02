//
// Created by ayman on 4/26/20.
//

#include <likha/GameEngine.h>
#include <cmath>

namespace likha {

GameEngine::GameEngine() {
  for (size_t i = 0; i < kNumPlayers; i++) {
    Player player = {
        0,
        i % 2 // Player 0 and 2 in team 0, Player 1 and 3 (gui) in team 1.
    };
    players_.push_back(player);
  }
  current_player_index_ = 0;
}


void GameEngine::RunGame() {

}

vector<vector<Card>> GameEngine::DealCards(Deck deck_) {
  for (const auto& player_ : players_) {
    vector<Card> cards_to_deal_;
    for (size_t i = 0; i < kNumCardsPerPlayer; i++) {
      cards_to_deal_.push_back(deck_.Draw());
    }
    player_hands_.push_back(cards_to_deal_);
  }
  return player_hands_;
}


/*
void GameEngine::GiftCards() {
  for (auto position = PlayerPosition(0); position < PlayerPosition::kNumPlayers; ((int&) position)++) {
    players_[((size_t) position)].strategy_ptr_->receiveGift( //receive gift from player to his left (ie. with next index)
        players_[((size_t) position + 1) % (size_t) PlayerPosition ::kNumPlayers].strategy_ptr_->giftCards());
  }
}
 */

size_t GameEngine::getCurrentPlayerIndex() {
  return 0;
}
void GameEngine::handlePlayedCard(Card card) {


  current_player_index_ = (current_player_index_ + 1) % kNumPlayers;
}

bool GameEngine::isValidCard() {
  return false;
}
void GameEngine::SetUp() {

}
void GameEngine::addUpScores() {
  for (size_t player_index = 0; player_index < kNumPlayers; player_index++) {
    size_t current_player_score_ = 0;
    for (const auto& card : player_cards_eaten_[player_index]) {
      current_player_score_ += card.GetPointValue();
    }
    players_[player_index].score_ += current_player_score_;
  }
}
size_t GameEngine::GetCurrentPlayerIndex() {
  return current_player_index_;
}

}