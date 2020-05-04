//
// Created by ayman on 4/26/20.
//

#include <likha/BasicPlayerStrategy.h>
#include <random>

using Suit = likha::Card::Suit;
using Rank = likha::Card::Rank;

namespace likha {

string BasicPlayerStrategy::chooseName() const {
  string name = "player" + std::to_string(std::random_device().operator()());
  return name;
}
void BasicPlayerStrategy::receiveNames(string teammate_name_, vector<string> opponent_names_) {

}
void BasicPlayerStrategy::receiveInitialCards(vector<Card> cards) {
    my_hand_ = cards;
    card_index_to_try_ = 0;
}
vector<Card> BasicPlayerStrategy::giftCards() {
  return vector<Card>({Card(Suit::Hearts, Rank::Six),
                       Card(Suit::Hearts, Rank::Six),
                       Card(Suit::Hearts, Rank::Six),});
}
Card BasicPlayerStrategy::playCard(vector<Card> cardsPlayed) {
  return my_hand_[card_index_to_try_];
}
void BasicPlayerStrategy::receiveMoveValidation(bool isValid) {
  if (!isValid) {
    card_index_to_try_++;
  }
}
void BasicPlayerStrategy::receiveCurrentScores(map<string, size_t> currentScores) {

}
void BasicPlayerStrategy::receiveGift(vector<Card> cards) {

}

}