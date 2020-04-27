//
// Created by ayman on 4/18/20.
//

#ifndef FINALPROJECT_INCLUDE_LIKHA_CARD_H_
#define FINALPROJECT_INCLUDE_LIKHA_CARD_H_

#include <glob.h>

namespace likha {

static constexpr size_t kHeartsValue = 1;
static constexpr size_t kTenDiamondsValue = 10;
static constexpr size_t kQueenSpadesValue = 13;
static constexpr size_t kNoValue = 0;

class Card {

 public:
  enum class Suit {
    Diamonds,
    Hearts,
    Spades,
    Clubs,
    kNumSuits
  };

  enum class Rank {
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace,
    kNumRanks
  };

  Card(Suit set_suit, Rank set_rank);
  size_t GetPointValue();
  Suit GetSuit() const;
  Rank GetRank() const;

  bool operator==(const Card& rhs) const;

 private:
  Suit suit;
  Rank rank;

};

}  // namespace likha


#endif //FINALPROJECT_SRC_CARD_H_
