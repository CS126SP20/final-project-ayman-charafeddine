//
// Created by ayman on 5/4/20.
//

#include <likha/GameEngine.h>
#include <likha/Card.h>
#include "likha/Trick.h"

namespace likha {

Trick::Trick(size_t opening_player) {
  opening_player_index_ = opening_player;
}

void Trick::AddCard(Card card_to_add_) {
  if (cards_in_trick_.empty()) {
    required_suit_ = card_to_add_.GetSuit();
  }
    cards_in_trick_.push_back(card_to_add_);
}

vector<Card> Trick::GetCards() {
  return cards_in_trick_;
}

bool Trick::TrickFinished() {
  return cards_in_trick_.size() == kNumPlayers;
}

size_t Trick::GetTrickEater() {
  //Assume opener eats
  Card highest_card = cards_in_trick_[0];
  size_t eater_index_ = opening_player_index_;

  for (size_t i = 1; i < kNumPlayers; i++) {
    if (cards_in_trick_[i].GetSuit() == required_suit_ && cards_in_trick_[i].GetRank() >= highest_card.GetRank()) {
      highest_card = cards_in_trick_[i];
      eater_index_ = (opening_player_index_ + i ) % kNumPlayers;
    }
  }
  return eater_index_;
}

Card::Suit Trick::GetRequiredSuit() {
  return required_suit_;
}

}