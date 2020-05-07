//
// Created by ayman on 4/26/20.
//

#ifndef FINALPROJECT_INCLUDE_LIKHA_BASICPLAYERSTRATEGY_H_
#define FINALPROJECT_INCLUDE_LIKHA_BASICPLAYERSTRATEGY_H_

#include "PlayerStartegy.h"

namespace likha {

/**
 * Implementation of PlayerStrategy that keeps returning a different card from its hand until the game_engine
 * accepts the card.
 */
class BasicPlayerStrategy : public PlayerStrategy {
 public:

  /**
   * Chooses name player + random int (eg. player29463947)
   * @return name as string
   */
  string ChooseName() const override;
  /**
   * Stores initial cards dealt.
   * @param cards my hand
   */
  void ReceiveInitialCards(vector<Card> cards) override;
  /**
   * Not implemented yet.
   * @return
   */
  vector<Card> GiftCards() override;
  /**
   * Not implemented yet.
   * @param cards
   */
  void ReceiveGift(vector<Card> cards) override;
  /**
   * Choose random card using a stored index that updates when card invalid.
   * @param cardsPlayed not used
   * @return random card
   */
  Card PlayCard(vector<Card> cardsPlayed) override;
  /**
   * Update index to try if card tried was invalid.
   * @param isValid
   */
  void ReceiveMoveValidation(bool isValid) override;
  /**
   * Not yet implemented.
   * @param current_scores_
   */
  void receiveCurrentScores(map<size_t, size_t> current_scores_) override;
  ~BasicPlayerStrategy() override = default;
 private:
  /** cards dealt to me*/
  vector<Card> my_hand_;
  /**index of card in hand to try to play. */
  size_t card_index_to_try_;
};

}

#endif //FINALPROJECT_INCLUDE_LIKHA_BASICPLAYERSTRATEGY_H_
