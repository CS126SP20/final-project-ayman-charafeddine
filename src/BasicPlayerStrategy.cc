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

}
vector<Card> BasicPlayerStrategy::giftCards() {
  return vector<Card>();
}
Card BasicPlayerStrategy::playCard(vector<Card> cardsPlayed) {
  return {Suit::Hearts, Rank::Six};
}
void BasicPlayerStrategy::receiveMoveValidation(string) {

}
void BasicPlayerStrategy::receiveCurrentScores(map<string, size_t> currentScores) {

}
void BasicPlayerStrategy::receiveGift(vector<Card> cards) {

}

}