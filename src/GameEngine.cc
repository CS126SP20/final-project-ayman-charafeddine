//
// Created by ayman on 4/26/20.
//

#include <likha/GameEngine.h>
#include <cmath>
#include <algorithm>
#include <likha/Card.h>

namespace likha {

using Suit = likha::Card::Suit;
using Rank = likha::Card::Rank;

const Card kDiamondLikha = Card(Suit::Diamonds, Rank::Ten);
const Card kSpadeLikha = Card(Suit::Spades, Rank::Queen);

GameEngine::GameEngine() {
  for (size_t i = 0; i < kNumPlayers; i++) {
    PlayerStats player = {
        0,
        i % 2 // Player 0 and 2 in team 0, Player 1 and 3 (gui) in team 1.
    };
    players_.push_back(player);
  }
  current_player_index_ = 0;
  player_cards_eaten_ = vector<vector<Card>>(4, vector<Card>());
  trick_ = Trick(0); //First player is 0
}

vector<vector<Card>> GameEngine::DealCards(Deck deck_) {
  player_hands_.clear();
  for (const auto& player_ : players_) {
    vector<Card> cards_to_deal_;
    for (size_t i = 0; i < kNumCardsPerPlayer; i++) {
      cards_to_deal_.push_back(deck_.Draw());
    }
    player_hands_.push_back(cards_to_deal_);
  }
  return player_hands_;
}

void GameEngine::HandleCard(Card card) {
  vector<Card>& current_hand_ = player_hands_[current_player_index_];
  //Remove card from player Hand
  current_hand_.erase(std::remove(current_hand_.begin(), current_hand_.end(), card),
                      current_hand_.end());
  //Add card to current trick
  trick_.AddCard(card);

  if (!trick_.TrickFinished()) {
    //Trick isn't over, go to next player
    current_player_index_ = (current_player_index_ + 1) % kNumPlayers;
  }

  if (IsRoundOver()) {
    HandleEndOfTrick();
    addUpScores();
    //Player that starts game is the one who ate the queen of spades
    current_player_index_ = GetQueenOfSpadesEater();
    player_cards_eaten_ = vector<vector<Card>>(4, vector<Card>());
  }
}

bool GameEngine::IsValidCard(Card card) {
  vector<Card> current_hand_ = player_hands_[current_player_index_];

  if (!VectorContainsCard(card, current_hand_)) {
    //Player does not have that card, card is invalid
    return false;
  }

  if (trick_.GetCards().empty()) {
    //First player in trick can play any card he has
    return true;
  }

  if (CurrentPlayerMustPlayLikha() && !card.IsLikha()) {
    //Player is required to play the Likha but is trying to play a different card, card is invalid
    return false;
  }
  if (CurrentPlayerHasSuit(trick_.GetRequiredSuit())) {
    //Player has the required suit, must play it
    return card.GetSuit() == trick_.GetRequiredSuit();
  }
  //Player does not have the required suit, can play anything
  return true;
}

void GameEngine::addUpScores() {
  for (size_t player_index = 0; player_index < kNumPlayers; player_index++) {
    size_t current_player_score_ = 0;
    for (const auto &card : player_cards_eaten_[player_index]) {
      current_player_score_ += card.GetPointValue();
    }
    players_[player_index].score_ += current_player_score_;
  }
}

size_t GameEngine::GetCurrentPlayerIndex() {
  return current_player_index_;
}

bool GameEngine::CurrentPlayerMustPlayLikha() {
  if (!CurrentPlayerHasLikhaOfSuit(Suit::Spades) && !CurrentPlayerHasLikhaOfSuit(Suit::Diamonds)) {
    return false; //Player doesn't have a likha
  }

  if (!CurrentPlayerHasSuit(trick_.GetRequiredSuit())) {
    return true; //Player doesn't have the required suit, so player must get rid of likha
  }

  if (trick_.GetRequiredSuit() == Suit::Spades || trick_.GetRequiredSuit() == Suit::Diamonds) {
    for (const auto &card : trick_.GetCards()) {
      if (card.EatsLikhaOfCurrentSuit(trick_.GetRequiredSuit()) && CurrentPlayerHasLikhaOfSuit(trick_.GetRequiredSuit())) {
        return true; //One of the cards played are higher than likha, so player must get rid of it
      }
    }
    return false;
  }
  return false;

}

bool GameEngine::CurrentPlayerHasSuit(Suit suit) {
  vector<Card> current_hand_ = player_hands_[current_player_index_];

  for (const auto &card : current_hand_) {
    if (card.GetSuit() == suit) {
      return true;
    }
  }
  return false;
}

bool GameEngine::VectorContainsCard(Card card, vector<Card> cards) {
  return (std::find(cards.begin(), cards.end(), card) != cards.end());
}

bool GameEngine::CurrentPlayerHasLikhaOfSuit(Suit suit_) {
  vector<Card> current_hand_ = player_hands_[current_player_index_];

  if (suit_ == Suit::Diamonds) {
    return VectorContainsCard(kDiamondLikha, current_hand_);
  }
  if (suit_ == Suit::Spades) {
    return VectorContainsCard(kSpadeLikha, current_hand_);
  }
  return false;
}

Trick GameEngine::GetCurrentTrick() {
  return trick_;
}

void GameEngine::HandleEndOfTrick() {
  size_t trick_eater_index_ = trick_.GetTrickEater();
  for (const auto &card_in_trick_ : trick_.GetCards()) {
    player_cards_eaten_[trick_eater_index_].push_back(card_in_trick_);
  }
  //Current trick eater should open the new trick
  current_player_index_ = trick_eater_index_;
  trick_ = Trick(current_player_index_);
}

bool GameEngine::IsRoundOver() {
  for (const auto& hand : player_hands_) {
    if (!hand.empty()) {
      return false;
    }
  }
  return true;
}
vector<GameEngine::PlayerStats> GameEngine::GetPlayerStats() {
  return players_;
}

size_t GameEngine::GetQueenOfSpadesEater() {
  for (size_t player_index = 0; player_index < kNumPlayers; player_index++) {
    for (const auto& card : player_cards_eaten_[player_index]) {
      if (card == Card(Suit::Spades, Rank::Queen)) {
        return player_index;
      }
    }
  }
}

}