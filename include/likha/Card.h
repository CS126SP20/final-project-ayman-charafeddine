//
// Created by ayman on 4/18/20.
//

#ifndef FINALPROJECT_INCLUDE_LIKHA_CARD_H_
#define FINALPROJECT_INCLUDE_LIKHA_CARD_H_

#include <glob.h>
#include <vector>
#include <string>

#include <cinder/gl/Texture.h>
#include <cinder/gl/draw.h>

namespace likha {

using std::string;
using std::vector;

using cinder::loadImage;
using cinder::Color;

static constexpr size_t kHeartsValue = 1;
static constexpr size_t kTenDiamondsValue = 10;
static constexpr size_t kQueenSpadesValue = 13;

static const vector<string> kSuitsStrings = {"diamonds", "spades", "hearts", "clubs"};
static const vector<string> kRanksStrings = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "j", "q", "k", "a"};
static const string
    kCardBackImagePath = "/home/ayman/Cinder/my-projects/final-project-ayman-charafeddine/assets/cards/back-red-1.png";

static constexpr float kCardImageHalfWidth = 37.5f;
static constexpr float kCardImageHalfLength = 53.5f;
static constexpr double kCardRotationSpeed = 10.0;
static constexpr float kCardPathLength = 250.0f;
static constexpr float kCardPathDelta = 8.0f;

class Card {

 public:
  enum class Suit {
    Diamonds,
    Spades,
    Hearts,
    Clubs,
    kNumSuits
  };

  enum class Rank {
    Two,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace,
    kNumRanks
  };

  Card(Suit set_suit, Rank set_rank);

  Suit GetSuit() const;

  Rank GetRank() const;

  /**
 * Get card's point value. 1 for all hearts, 13 for Q of Spades, 10 for 10 of Diamonds.
 * @return point value
 */
  size_t GetPointValue() const;

  /**
   * Return true if rank and suit are the same.
   */
  bool operator==(const Card &rhs) const;

  /**
   * Return true if card is Q of Spades or 10 of Diamonds.
   */
  bool IsLikha() const;

  /**
   * Return true if card is of required_suit_ and higher rank than the likha of that suit.
   * @param required_suit_ : The suit that is required to eat the current trick.
   */
  bool EatsLikhaOfCurrentSuit(Suit required_suit_) const;

  /**
   * Get the file path of the image corresponding to the card.
   */
  string GetCardImagePath() const;

  /**
   * Comparator for sorting by suit
   */
   static bool CompareSuits(const Card &first, const Card &second);

   /**
    * Comparator for sorting by rank
    */
    static bool CompareRanks(const Card &first, const Card &second);

 private:
  Suit suit;
  Rank rank;

};

}  // namespace likha


#endif //FINALPROJECT_SRC_CARD_H_
