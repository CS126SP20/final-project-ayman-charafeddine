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
  card_texture_ = cinder::gl::Texture::create(loadImage("/home/ayman/Cinder/my-projects/final-project-ayman-charafeddine/assets/cards/back-red-1.png"));
  center_ = set_center_;
  elapsed_seconds_ = set_elapsed_seconds_;
}
void Dealer::Update(double new_elapsed_seconds_) {
  elapsed_seconds_ = new_elapsed_seconds_;

  if (card_pos_change_ < kCardPathLength) {
    card_pos_change_ += kCardPathDelta;
  } else {
    card_pos_change_ = 0;
    cards_dealt_++;
  }

  cinder::gl::draw(card_texture_, center_);

  cinder::gl::pushModelView();
  if (cards_dealt_ >= 0 && cards_dealt_ < kNumCardsPerPlayer) {
    cinder::gl::translate(center_.x - card_pos_change_, center_.y);
  } else if (cards_dealt_ >= kNumCardsPerPlayer && cards_dealt_ < 2 * kNumCardsPerPlayer) {
    cinder::gl::translate(center_.x, center_.y - card_pos_change_);
  } else if (cards_dealt_ >= 2 * kNumCardsPerPlayer && cards_dealt_ < 3 * kNumCardsPerPlayer) {
    cinder::gl::translate(center_.x + card_pos_change_, center_.y);
  } else if (cards_dealt_ >= 3 * kNumCardsPerPlayer && cards_dealt_ < 4 * kNumCardsPerPlayer) {
    cinder::gl::translate(center_.x, center_.y  + card_pos_change_);
  }
  cinder::gl::rotate(float(elapsed_seconds_ * kRotationSpeed));
  cinder::gl::translate(-kImageHalfWidth, -kImageHalfLength);
  cinder::gl::draw(card_texture_);
  cinder::gl::popModelView();
}

string Dealer::GetCardImagePath(likha::Card card) {
  string suit = suits[(size_t) card.GetSuit()];
  string rank = ranks[(size_t) card.GetRank()];
  return "/home/ayman/Cinder/my-projects/final-project-ayman-charafeddine/assets/cards/" + suit + "-" + rank + ".png";
}
bool Dealer::DealingComplete() {
  return cards_dealt_ >= 4 * kNumCardsPerPlayer;
}

Dealer::Dealer() = default;

}