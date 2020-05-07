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

  /**
   * Only to be called when round is over. Updates scores based on the cards eaten in a round.
   */
  void AddUpScores();
  /**
   * Return whether or not the current player is obligated to play a likha (if you have the chance to get rid of a likha
   * you must play it).
   */
  bool CurrentPlayerMustPlayLikha();
  /**
   * Returns whether current player has a card of the suit given.
   */
  bool CurrentPlayerHasSuit(Card::Suit suit);
  /**
   * Return the index of the player who ate the queen of spades (and will start next round).
   */
  size_t GetQueenOfSpadesEater();
  /**
   * Returns whether the current player has the likha of suit given (Ten of Diamonds or Queen of Spades).
   */
  bool CurrentPlayerHasLikhaOfSuit(Card::Suit suit_);

  size_t current_player_index_;
  /** The current cards that each player has */
  vector<vector<Card>> player_hands_;
  /**The stats (team and score) of each player*/
  vector<PlayerStats> players_stats_;
  /**List of cards player has eaten in current round*/
  vector<vector<Card>> player_cards_eaten_;
  /** Current trick being played*/
  Trick trick_ = Trick(0);

  // void GiftCards();

 public:

  explicit GameEngine();
  /**
   * Saves the hands of each player for move validation and returns the hands to the app.
   * @param deck_ Deck object to deal from.
   */
  vector<vector<Card>> DealCards(Deck deck_);

  size_t GetCurrentPlayerIndex();
  Trick GetCurrentTrick();

  /**
   * Only to be called if card is known to be valid. Updates game engine state and checks if entire round is over to
   * start a new one.
   * @param card
   */
  void HandleCard(Card card);
  /**
   * Returns whether a card is a valid move or not based on the rules of the game.
   */
  bool IsValidCard(Card card);

  /**
   * Only to be called once trick is over. Adds up cards eaten for each player and sets up the new trick and
   * new current player index.
   */
  void HandleEndOfTrick();
  /**
   * Returns whther round is over
   */
  bool IsRoundOver();
  /**
   * Returns whether game is over.
   */
  bool IsGameOver();
  /**
   * Returns the stats of all the players.
   */
  vector<PlayerStats> GetPlayerStats();

  /**
   * Returns who which team lost the game ie. which team has a player who is above the losing threshold.
   */
  size_t GetLosingTeam();

  /**
   * Return whether a  vector contains a card.
   */
  static bool VectorContainsCard(Card card_to_find_, vector<Card> cards);

};

}

#endif //FINALPROJECT_INCLUDE_LIKHA_GAMEENGINE_H_
