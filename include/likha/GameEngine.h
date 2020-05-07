//
// Created by ayman on 4/26/20.
//

#ifndef FINALPROJECT_INCLUDE_LIKHA_GAMEENGINE_H_
#define FINALPROJECT_INCLUDE_LIKHA_GAMEENGINE_H_

#include "Card.h"
#include "Deck.h"
#include "PlayerStartegy.h"
#include "Trick.h"

using std::vector;
using std::string;

namespace likha {

static constexpr size_t kNumPlayers = 4;
static constexpr size_t kLosingScore = 20;

class GameEngine {
 public:
  struct PlayerStats {
    size_t score_;
    size_t team_;
  };

 private:
  void addUpScores();

  size_t current_player_index_;
  vector<vector<Card>> player_hands_;
  vector<PlayerStats> players_;
  vector<vector<Card>> player_cards_eaten_;
  Trick trick_ = Trick(0);

  // void GiftCards();

 public:

  explicit GameEngine();

  size_t GetCurrentPlayerIndex();
  vector<vector<Card>> DealCards(Deck deck_);
  Trick GetCurrentTrick();

  void HandleCard(Card card);
  bool CurrentPlayerMustPlayLikha();
  bool CurrentPlayerHasSuit(Card::Suit suit);
  static bool VectorContainsCard(Card card, vector<Card> cards);
  bool CurrentPlayerHasLikhaOfSuit(Card::Suit suit_);
  bool IsValidCard(Card card);
  void HandleEndOfTrick();
  bool IsRoundOver();
  vector<PlayerStats> GetPlayerStats();
  bool IsGameOver();

  size_t GetQueenOfSpadesEater();
  size_t GetLosingTeam();
};

}

#endif //FINALPROJECT_INCLUDE_LIKHA_GAMEENGINE_H_
