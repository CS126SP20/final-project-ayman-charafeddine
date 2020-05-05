//
// Created by ayman on 4/26/20.
//

#ifndef FINALPROJECT_INCLUDE_LIKHA_GAMEENGINE_H_
#define FINALPROJECT_INCLUDE_LIKHA_GAMEENGINE_H_

#include "Card.h"
#include "Deck.h"
#include "PlayerStartegy.h"


using std::vector;
using std::string;

namespace likha {

static constexpr size_t kNumPlayers = 4;

class GameEngine {
 private:
  struct Player {
    size_t score_;
    size_t team_;
  };

  bool isValidCard(Card card);
  void addUpScores();

  size_t current_player_index_;
  vector<vector<Card>> player_hands_;
  vector<Player> players_;
  vector<vector<Card>> player_cards_eaten_;
  bool last_card_was_valid_{};
  Card::Suit current_suit_;
  vector<Card> current_trick_;


  // void GiftCards();

 public:

  explicit GameEngine();

  size_t GetCurrentPlayerIndex();
  vector<vector<Card>> DealCards(Deck deck_);
  void SetUp();
  void RunGame();
  bool HandleAndValidateCard(Card card);
  bool TrickIsOngoing();

  bool MustPlayLikha();
  bool HasSuit(Card::Suit suit);
  static bool vecContainsCard(Card card, vector<Card> cards);
  bool HasLikhaOfSuit(Card::Suit suit_);
  size_t GetCurrentTrickEaterIndex();
};

}

#endif //FINALPROJECT_INCLUDE_LIKHA_GAMEENGINE_H_
