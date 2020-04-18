//
// Created by ayman on 4/18/20.
//

#ifndef FINALPROJECT_SRC_CARD_H_
#define FINALPROJECT_SRC_CARD_H_

#include <glob.h>
namespace likha {

class Card {
 private:
  constexpr size_t kHeartsValue = 1;
  constexpr size_t kTenDiamonds = 10;
  constexpr size_t kQueenSpades = 13;
  constexpr size_t kNoValue = 0;

  Suit suit;
  Rank rank;

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
  Suit GetSuit();
  Rank GetRank();

};

}  // namespace likha


#endif //FINALPROJECT_SRC_CARD_H_
