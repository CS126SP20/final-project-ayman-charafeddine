//
// Created by ayman on 4/26/20.
//

#ifndef FINALPROJECT_INCLUDE_LIKHA_BASICPLAYERSTRATEGY_H_
#define FINALPROJECT_INCLUDE_LIKHA_BASICPLAYERSTRATEGY_H_

#include "PlayerStartegy.h"

namespace likha {

class BasicPlayerStrategy : public PlayerStrategy {
 public:
  string chooseName() const override;
  void receiveNames(string teammate_name_, vector<string> opponent_names_) override;
  void receiveInitialCards(vector<Card> cards) override;
  vector<Card> giftCards() override;
  void receiveGift(vector<Card> cards) override;
  Card playCard(vector<Card> cardsPlayed) override;
  void receiveMoveValidation(bool isValid) override;
  void receiveCurrentScores(map<string, size_t> currentScores) override;
  ~BasicPlayerStrategy() override = default;
 private:
  vector<Card> my_hand_;
  bool move_is_valid_;
  size_t card_index_to_try_;
};

//TODO fix naming to fit google style

}

#endif //FINALPROJECT_INCLUDE_LIKHA_BASICPLAYERSTRATEGY_H_
