#ifndef FINALPROJECT_INCLUDE_LIKHA_TRICK_H_
#define FINALPROJECT_INCLUDE_LIKHA_TRICK_H_

#include <likha/Card.h>

namespace likha {

class Trick {
 public:
  Trick(size_t opening_player);

  /**
   * Add card being played to trick.
   */
  void AddCard(Card card_to_add_);

  vector<Card> GetCards();

  /**
   * Return whether the trick is finished or not
   */
  bool TrickFinished();

  /**
   * Returns who eats this trick. Only to be called when trick is finished.
   * @return index of player who eats the trick.
   */
  size_t GetTrickEater();

  Card::Suit GetRequiredSuit();

 private:
  vector<Card> cards_in_trick_;
  size_t opening_player_index_;
  Card::Suit required_suit_;


};

}

#endif //FINALPROJECT_INCLUDE_LIKHA_TRICK_H_