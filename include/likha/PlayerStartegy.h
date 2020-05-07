//
// Created by ayman on 4/26/20.
//

#ifndef FINALPROJECT_INCLUDE_LIKHA_PLAYERSTARTEGY_H_
#define FINALPROJECT_INCLUDE_LIKHA_PLAYERSTARTEGY_H_

#include <vector>
#include <string>
#include <map>

#include "Card.h"

using std::vector;
using std::string;
using std::map;

namespace likha {

class PlayerStrategy {
 public:
  /**
   * Choose your name. To be used in future implementation,
   * to know which implementation of PlayerStrategy you're playing with.
   * @return name as string
   */
  virtual string ChooseName() const = 0;
  /**
   * Receive initial cards dealt and act or store as needed.
   * @param cards_
   */
  virtual void ReceiveInitialCards(vector<Card> cards_) = 0;
  /**
   * Choose cards to gift. To be used in future implementation of gifting.
   * @return
   */
  virtual vector<Card> GiftCards() = 0;
  /**
   * Receive your gift and store as needed.
   * @param gift_
   */
  virtual void ReceiveGift(vector<Card> gift_) = 0;
  /**
   * Choose card to play based on current trick.
   * @param current_trick_ cards played so far in trick
   * @return card chosen to be played
   */
  virtual Card PlayCard(vector<Card> current_trick_) = 0;
  /**
   * receive whether or not the card previously played was valid.
   * @param is_valid_
   */
  virtual void ReceiveMoveValidation(bool is_valid_) = 0;
  /**
   * Receive current scores. To be used in future implementation
   * so that PlayerStrategies can choose what to play based on current scores
   * @param current_scores_
   */
  virtual void receiveCurrentScores(map<size_t, size_t> current_scores_) = 0;
  /**
   * virtual Destructor to allow for child classes to be stored as PlayerStrategy pointers.
   */
  virtual ~PlayerStrategy() = default;
};

}

#endif //FINALPROJECT_INCLUDE_LIKHA_PLAYERSTARTEGY_H_
