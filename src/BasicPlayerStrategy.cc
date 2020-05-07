//
// Created by ayman on 4/26/20.
//

#include <likha/BasicPlayerStrategy.h>
#include <random>

using Suit = likha::Card::Suit;
using Rank = likha::Card::Rank;

namespace likha {

string BasicPlayerStrategy::ChooseName() const {
  string name = "player" + std::to_string(std::random_device().operator()());
  return name;
}

void BasicPlayerStrategy::ReceiveInitialCards(vector<Card> cards) {
    my_hand_ = cards;
    card_index_to_try_ = 0;
}
vector<Card> BasicPlayerStrategy::GiftCards() {
  return vector<Card>();
}
Card BasicPlayerStrategy::PlayCard(vector<Card> current_trick_) {
  //Keep randomly playing card in hand, if not valid, index is updated in ReceiveMoveValidation method
  return my_hand_[card_index_to_try_];
}
void BasicPlayerStrategy::ReceiveMoveValidation(bool isValid) {
  if (!isValid) {
    card_index_to_try_ = (card_index_to_try_ + 1) % my_hand_.size();
  }
}

void BasicPlayerStrategy::receiveCurrentScores(map<size_t, size_t> current_scores_) {

}

void BasicPlayerStrategy::ReceiveGift(vector<Card> cards) {

}

}