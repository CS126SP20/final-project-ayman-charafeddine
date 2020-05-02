//
// Created by ayman on 4/29/20.
//

#ifndef FINALPROJECT_APPS_DEALER_H_
#define FINALPROJECT_APPS_DEALER_H_

#include <likha/GameEngine.h>
#include <cinder/gl/Texture.h>

namespace likha {

namespace gui {

static const vector<string> suits = {"diamonds", "hearts", "spades", "clubs"};
static const vector<string> ranks = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "j", "q", "k", "a"};
static constexpr float kImageHalfWidth = 37.5f;
static constexpr float kImageHalfLength = 53.5f;
static constexpr double kRotationSpeed = 10.0;
static constexpr float kCardPathLength = 250.0f;
static constexpr float kCardPathDelta = 20.0f;

class Dealer {
 public:
  Dealer(PlayerPosition set_position_, const cinder::vec2 &set_center_, double set_elapsed_seconds_);
  Dealer();
  void Update(double new_elapsed_seconds_);
  static string GetCardImagePath(Card card);
  bool DealingComplete();
 private:
  PlayerPosition position_;
  cinder::gl::TextureRef card_texture_;
  size_t cards_dealt_{};
  float card_pos_change_{};
  cinder::vec2 center_;
  double elapsed_seconds_{};

};

}

}
#endif //FINALPROJECT_APPS_DEALER_H_
