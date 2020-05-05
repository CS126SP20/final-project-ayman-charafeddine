//
// Created by ayman on 4/18/20.
//

#include <cstddef>
#include <likha/Card.h>
#include <cinder/gl/gl.h>
#include "likha/Card.h"



namespace likha {


const Card kDiamondLikha = Card(Card::Suit::Diamonds, Card::Rank::Ten);
const Card kSpadeLikha = Card (Card::Suit::Spades, Card::Rank::Queen);

Card::Card(Card::Suit set_suit, Card::Rank set_rank) {
  suit = set_suit;
  rank = set_rank;
  card_drawn_ = false;
  card_current_x_position_ = kCardPathLength;
  card_current_y_position_ = 900;
}

size_t Card::GetPointValue() const {
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

bool Card::IsLikha() const {
  return (suit == Suit::Spades && rank == Rank::Queen)
  || (suit == Suit::Diamonds && rank == Rank::Ten);
}

bool Card::EatsLikha(Suit current_suit_) const {
  if (current_suit_ == Suit::Spades) {
    return rank > kSpadeLikha.rank;
  }
  if (current_suit_ == Suit::Diamonds) {
    return rank > kDiamondLikha.rank;
  }
  return false;
}

string Card::GetCardImagePath() const {
  string suit_string_ = suits[(size_t) suit];
  string rank_string_ = ranks[(size_t) rank];
  return "/home/ayman/Cinder/my-projects/final-project-ayman-charafeddine/assets/cards/" + suit_string_ + "-" + rank_string_ + ".png";
}

bool Card::HasCardBeenDrawn() {
  return card_drawn_;
}
} //namespace likha