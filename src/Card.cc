//
// Created by ayman on 4/18/20.
//

#include <cstddef>
#include "likha/Card.h"

namespace likha {

Card::Card(Card::Suit set_suit, Card::Rank set_rank) {
  suit = set_suit;
  rank = set_rank;
}

size_t Card::GetPointValue() {
  if (suit == Suit::Hearts) {
    return kHeartsValue;
  }

  if (suit == Suit::Diamonds && rank == Rank::Ten) {
    return kTenDiamondsValue;
  }

  if (suit == Suit::Spades && rank == Rank::Queen) {
    return kQueenSpadesValue;
  }

  return kNoValue;
}

Card::Suit Card::GetSuit() const {
  return suit;
}

Card::Rank Card::GetRank() const {
  return rank;
}
bool Card::operator==(const Card& rhs) const {
  return rhs.GetRank() == rank && rhs.GetSuit() == suit;
}

} //namespace likha