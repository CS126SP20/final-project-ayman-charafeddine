//
// Created by ayman on 4/18/20.
//

#ifndef FINALPROJECT_SRC_CARD_H_
#define FINALPROJECT_SRC_CARD_H_

#include <glob.h>
namespace likha {

class Card {

 public:
  enum class Suit {
    Diamonds,
    Hearts,
    Spades,
    Clubs
  };

  enum class Rank {
    One,
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
    King
  };

  Card(Suit set_suit, Rank set_rank);
  size_t GetPointValue();
  Suit GetSuit() const;
  Rank GetRank() const;

  bool operator==(const Card& rhs) const;

 private:
  static constexpr size_t kHeartsValue = 1;
  static constexpr size_t kTenDiamondsValue = 10;
  static constexpr size_t kQueenSpadesValue = 13;
  static constexpr size_t kNoValue = 0;

  Suit suit;
  Rank rank;

};

}  // namespace likha


#endif //FINALPROJECT_SRC_CARD_H_
