//
// Created by ayman on 4/18/20.
//

#include <cstddef>
#include "likha/Card.h"

namespace likha {

Card::Card(Card::Suit set_suit, Card::Rank set_rank) {

}

size_t Card::GetPointValue() {
  if (suit == Suit::Hearts) {
    return kHeartsValue;
  }

  if (suit == Suit::Diamonds && rank == Rank::Ten) {
    return kTenDiamonds;
  }

  if (suit == Suit::Spades && rank == Rank::Queen) {
    return kQueenSpades;
  }

  return kNoValue;
}

Card::Suit Card::GetSuit() {
  return suit;
}
Card::Rank Card::GetRank() {
  return rank;
}

} //namespace likha