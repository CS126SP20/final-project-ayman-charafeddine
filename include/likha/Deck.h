//
// Created by ayman on 4/18/20.
//

#ifndef FINALPROJECT_INCLUDE_LIKHA_DECK_H_
#define FINALPROJECT_INCLUDE_LIKHA_DECK_H_

#include <stack>
#include "Card.h"

namespace likha {

static constexpr size_t kDeckSize = 52;
static constexpr size_t kNumCardsPerPlayer = 13;

class Deck {
 private:
  std::stack<Card> deck_of_cards_;

 public:
  /**
   * Constructs a Deck object with a stack of each of the 52 cards, and that's randomly shuffled.
   */
  Deck();
  /**
   * Returns the top card and pops it from the stack.
   */
  Card Draw();
  /**
   * Returns size of stack.
   */
  size_t size() const;

};

}



#endif //FINALPROJECT_INCLUDE_LIKHA_DECK_H_
