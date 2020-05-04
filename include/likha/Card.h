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
static constexpr size_t kNoValue = 0;

static const vector<string> suits = {"diamonds", "hearts", "spades", "clubs"};
static const vector<string> ranks = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "j", "q", "k", "a"};
static const string kCardBackImagePath = "/home/ayman/Cinder/my-projects/final-project-ayman-charafeddine/assets/cards/back-red-1.png";

static constexpr float kCardImageHalfWidth = 37.5f;
static constexpr float kCardImageHalfLength = 53.5f;
static constexpr double kCardRotationSpeed = 10.0;
static constexpr float kCardPathLength = 250.0f;
static constexpr float kCardPathDelta = 20.0f;

class Card {

 public:
  enum class Suit {
    Diamonds,
    Hearts,
    Spades,
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
  size_t GetPointValue() const;
  Suit GetSuit() const;
  Rank GetRank() const;

  bool operator==(const Card& rhs) const;

  bool IsLikha() const;
  bool EatsLikha(Suit current_suit_) const;

  string GetCardImagePath() const;
  void DrawCardPlayed(size_t current_index_, cinder::vec2 center_, double elapsed_seconds_);
  bool HasCardBeenDrawn();

 private:
  Suit suit;
  Rank rank;
  bool card_drawn_;
  float card_current_x_position_;
  float card_current_y_position_;

};

}  // namespace likha


#endif //FINALPROJECT_SRC_CARD_H_
