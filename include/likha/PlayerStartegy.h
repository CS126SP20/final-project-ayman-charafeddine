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
  virtual string chooseName() const = 0;
  virtual void receiveNames(string teammateName, vector<string> opponentNames) = 0;
  virtual void receiveInitialCards(vector<Card> cards) = 0;
  virtual vector<Card> giftCards() = 0;
  virtual Card playCard(vector<Card> cardsPlayed) = 0;
  virtual void receiveMoveValidation(string) = 0;
  virtual void receiveCurrentScores(map<string, size_t> currentScores) = 0;
  virtual ~PlayerStrategy() = default;
};

}

#endif //FINALPROJECT_INCLUDE_LIKHA_PLAYERSTARTEGY_H_
