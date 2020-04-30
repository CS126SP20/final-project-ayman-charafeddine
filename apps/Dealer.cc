//
// Created by ayman on 4/29/20.
//

#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <cinder/ImageIo.h>
#include "Dealer.h"

namespace gui {

using cinder::loadImage;
using cinder::Color;

Dealer::Dealer(PlayerPosition set_position_, const cinder::vec2& set_center_, double set_elapsed_seconds_) {
  position_ = set_position_;
  card_texture_ = cinder::gl::Texture::create(loadImage("/home/ayman/Cinder/my-projects/final-project-ayman-charafeddine/assets/cards/back-red-75-1.png"));
  center_ = set_center_;
  elapsed_seconds_ = set_elapsed_seconds_;
}
void Dealer::Update(double new_elapsed_seconds_) {
  elapsed_seconds_ = new_elapsed_seconds_;

  if (card_pos_change_ < 250.0f) {
    card_pos_change_ += 10.0f;
  } else {
    card_pos_change_ = 0;
    cards_dealt_++;
  }

  cinder::gl::draw(card_texture_, center_);

  cinder::gl::pushModelView();
  if (cards_dealt_ >= 0 && cards_dealt_ < 13) {
    cinder::gl::translate(center_.x - card_pos_change_, center_.y);
  } else if (cards_dealt_ >= 13 && cards_dealt_ < 26) {
    cinder::gl::translate(center_.x, center_.y - card_pos_change_);
  } else if (cards_dealt_ >= 26 && cards_dealt_ < 39) {
    cinder::gl::translate(center_.x + card_pos_change_, center_.y);
  } else if (cards_dealt_ >= 39 && cards_dealt_ < 52) {
    cinder::gl::translate(center_.x, center_.y  + card_pos_change_);
  }
  cinder::gl::rotate(float(elapsed_seconds_ * 8.0));
  cinder::gl::translate(-37.5f, -53.5f);
  cinder::gl::draw(card_texture_);
  cinder::gl::popModelView();
}
Dealer::Dealer() = default;

}