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
  void receiveGift() override;
  Card playCard(vector<Card> cardsPlayed) override;
  void receiveMoveValidation(string) override;
  void receiveCurrentScores(map<string, size_t> currentScores) override;
  ~BasicPlayerStrategy() override = default;
};

//TODO fix naming to fit google style

}

#endif //FINALPROJECT_INCLUDE_LIKHA_BASICPLAYERSTRATEGY_H_
