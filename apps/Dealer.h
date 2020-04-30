//
// Created by ayman on 4/29/20.
//

#ifndef FINALPROJECT_APPS_DEALER_H_
#define FINALPROJECT_APPS_DEALER_H_

#include <likha/GameEngine.h>
#include <cinder/gl/Texture.h>

namespace gui {

using namespace likha;

class Dealer {
 public:
  Dealer(PlayerPosition set_position_, const cinder::vec2& set_center_, double set_elapsed_seconds_);
  Dealer();
  void Update(double new_elapsed_seconds_);
 private:
  PlayerPosition position_;
  cinder::gl::TextureRef card_texture_;
  size_t cards_dealt_{};
  float card_pos_change_{};
  cinder::vec2 center_;
  double elapsed_seconds_{};


};

}
#endif //FINALPROJECT_APPS_DEALER_H_
