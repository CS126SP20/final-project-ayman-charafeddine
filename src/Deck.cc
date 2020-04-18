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

  for (Suit suit = Suit::Diamonds; suit <= Suit::Spades; ((int&) suit)++) {
    for (Rank rank = Rank::One; rank <= Rank::King; ((int&) rank)++) {
      tmp_cards_vector_.push_back(Card(suit, rank));
    }
  }

  //Shuffle cards
  std::shuffle(tmp_cards_vector_.begin(), tmp_cards_vector_.end(), std::random_device());

  //Add cards to stack
  for (const auto& card : tmp_cards_vector_) {
    deck_of_cards_.push(card);
  }
}


}