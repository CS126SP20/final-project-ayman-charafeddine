//
// Created by ayman on 4/26/20.
//

#include <likha/GameEngine.h>
#include <cmath>
#include <algorithm>
#include <likha/Card.h>

namespace likha {

using Suit = likha::Card::Suit;
using Rank = likha::Card::Rank;

const Card kDiamondLikha = Card(Suit::Diamonds, Rank::Ten);
const Card kSpadeLikha = Card(Suit::Spades, Rank::Queen);

GameEngine::GameEngine() {
  for (size_t i = 0; i < kNumPlayers; i++) {
    Player player = {
        0,
        i % 2 // Player 0 and 2 in team 0, Player 1 and 3 (gui) in team 1.
    };
    players_.push_back(player);
  }
  current_player_index_ = 0;
  last_card_was_valid_ = false;
  current_suit_ = Suit::kNumSuits;
  player_cards_eaten_ = vector<vector<Card>>(4, vector<Card>());
}

void GameEngine::RunGame() {

}

vector<vector<Card>> GameEngine::DealCards(Deck deck_) {
  for (const auto &player_ : players_) {
    vector<Card> cards_to_deal_;
    for (size_t i = 0; i < kNumCardsPerPlayer; i++) {
      cards_to_deal_.push_back(deck_.Draw());
    }
    player_hands_.push_back(cards_to_deal_);
  }
  return player_hands_;
}

/*
void GameEngine::GiftCards() {
  for (auto position = PlayerPosition(0); position < PlayerPosition::kNumPlayers; ((int&) position)++) {
    players_[((size_t) position)].strategy_ptr_->receiveGift( //receive gift from player to his left (ie. with next index)
        players_[((size_t) position + 1) % (size_t) PlayerPosition ::kNumPlayers].strategy_ptr_->giftCards());
  }
}
 */


void GameEngine::HandleCard(Card card) {
  if (current_trick_.empty()) {
    current_suit_ = card.GetSuit();
  }
  vector<Card> &current_hand_ = player_hands_[current_player_index_];
  //Remove card from player Hand
  current_hand_.erase(std::remove(current_hand_.begin(), current_hand_.end(), card),
                      current_hand_.end());
  //Add card to current trick
  current_trick_.push_back(card);
  if (current_trick_.size() < kNumPlayers) {
    //Trick isn't over, go to next player
    current_player_index_ = (current_player_index_ + 1) % kNumPlayers;
  }
}

bool GameEngine::isValidCard(Card card) {
  vector<Card> current_hand_ = player_hands_[current_player_index_];

  if (!vecContainsCard(card, current_hand_)) {
    //Player does not have that card, card is invalid
    return false;
  }

  if (current_trick_.empty()) {
    //First player in trick can play any card he has
    return true;
  }
  if (MustPlayLikha() && !card.IsLikha()) {
    //Player is required to play the Likha but is trying to play a different card, card is invalid
    return false;
  }
  if (HasSuit(current_suit_)) {
    //Player has the required suit, must play it
    return card.GetSuit() == current_suit_;
  }
  //Player does not have the required suit, can play anything
  return true;
}

void GameEngine::SetUp() {

}

void GameEngine::addUpScores() {
  for (size_t player_index = 0; player_index < kNumPlayers; player_index++) {
    size_t current_player_score_ = 0;
    for (const auto &card : player_cards_eaten_[player_index]) {
      current_player_score_ += card.GetPointValue();
    }
    players_[player_index].score_ += current_player_score_;
  }
}

size_t GameEngine::GetCurrentPlayerIndex() {
  return current_player_index_;
}

bool GameEngine::MustPlayLikha() {
  if (!HasLikhaOfSuit(Suit::Spades) && !HasLikhaOfSuit(Suit::Diamonds)) {
    return false; //Player doesn't have a likha
  }

  if (!HasSuit(current_suit_)) {
    return true; //Player doesn't have the required suit, so player must get rid of likha
  }

  if (current_suit_ == Suit::Spades || current_suit_ == Suit::Diamonds) {
    for (const auto &card : current_trick_) {
      if (card.EatsLikhaOfCurrentSuit(current_suit_) && HasLikhaOfSuit(current_suit_)) {
        return true; //One of the cards played are higher than likha, so player must get rid of it
      }
    }
    return false;
  }
  return false;

}

bool GameEngine::HasSuit(Suit suit) {
  vector<Card> current_hand_ = player_hands_[current_player_index_];

  for (const auto &card : current_hand_) {
    if (card.GetSuit() == suit) {
      return true;
    }
  }
  return false;
}

bool GameEngine::vecContainsCard(Card card, vector<Card> cards) {
  return (std::find(cards.begin(), cards.end(), card) != cards.end());
}

bool GameEngine::HasLikhaOfSuit(Suit suit_) {
  vector<Card> current_hand_ = player_hands_[current_player_index_];

  if (suit_ == Suit::Diamonds) {
    return vecContainsCard(kDiamondLikha, current_hand_);
  }
  if (suit_ == Suit::Spades) {
    return vecContainsCard(kSpadeLikha, current_hand_);
  }
  return false;
}

size_t GameEngine::GetCurrentTrickEaterIndex() {
  Card highest_card(current_suit_, Rank::Two); //lowest possible card that can eat the trick
  size_t eater_index_;
  size_t opening_player_index_ = (current_player_index_ + 1) % kNumPlayers; //Index of player who opened the trick
  for (size_t i = opening_player_index_; i < kNumPlayers + opening_player_index_; i++) {
    if (current_trick_[i % kNumPlayers].GetSuit() == current_suit_
        && current_trick_[i % kNumPlayers].GetRank() >= highest_card.GetRank()) {
      eater_index_ = i % kNumPlayers;
      highest_card = current_trick_[i % kNumPlayers];
    }
  }
  return eater_index_;
}
bool GameEngine::TrickIsOngoing() {
  return !current_trick_.empty();
}
vector<Card> GameEngine::GetCurrentTrick() {
  return current_trick_;
}
Card::Suit GameEngine::GetCurrentSuit() {
  return current_suit_;
}
void GameEngine::HandleEndOfTrick() {
  size_t trick_eater_index_ = GetCurrentTrickEaterIndex();
  for (const auto &card_in_trick_ : current_trick_) {
    player_cards_eaten_[trick_eater_index_].push_back(card_in_trick_);
  }
  //Current trick eater should open the new trick
  current_player_index_ = trick_eater_index_;
  current_trick_.clear();
}

}