//
// Created by ayman on 4/18/20.
//

#include "likha/Deck.h"
#include <vector>
#include <algorithm>
#include <random>

using Suit = likha::Card::Suit;
using Rank = likha::Card::Rank;

namespace likha {

Deck::Deck() {
  std::vector<Card> tmp_cards_vector_;

  for (auto suit = Suit(0); suit < Suit::kNumSuits; ((int&) suit)++) {
    for (auto rank = Rank(0); rank < Rank::kNumRanks; ((int&) rank)++) {
      tmp_cards_vector_.emplace_back(suit, rank);
    }
  }

  //Shuffle cards
  std::shuffle(tmp_cards_vector_.begin(), tmp_cards_vector_.end(), std::random_device());

  //Add cards to stack
  for (const auto& card : tmp_cards_vector_) {
    deck_of_cards_.push(card);
  }
}

Card Deck::Draw() {
  Card to_return_ = deck_of_cards_.top();
  deck_of_cards_.pop();
  return to_return_;
}

size_t Deck::size() const{
  return deck_of_cards_.size();
}

}