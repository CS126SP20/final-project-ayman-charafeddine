//
// Created by ayman on 5/3/20.
//

#include <cinder/gl/gl.h>
#include "likha/CardDrawer.h"

namespace likha {

CardDrawer::CardDrawer() {
  should_draw_ = false;
}

CardDrawer::CardDrawer(const vec2 &start_position_, const vec2 &end_position_, Card card, bool rotate_) {
  should_draw_ = true;
  current_position_ = start_position_;
  ending_position_ = end_position_;
  card_texture_ = cinder::gl::Texture::create(loadImage(card.GetCardImagePath()));
  should_rotate_ = rotate_;
}

CardDrawer::CardDrawer(const vec2 &start_position_, const vec2 &end_position_, bool rotate_) {
  should_draw_ = true;
  current_position_ = start_position_;
  ending_position_ = end_position_;
  card_texture_ = cinder::gl::Texture::create(loadImage(kCardBackImagePath));
  should_rotate_ = rotate_;
}

void CardDrawer::UpdateAndDraw(double elapsed_seconds_) {
  if (should_draw_) {
    if (current_position_ == ending_position_) {
      cinder::gl::draw(card_texture_, current_position_);
    } else {

      //If card is really close to end position, just take it there
      if (std::abs(current_position_.x - ending_position_.x) < kCardPathDelta) {
        current_position_.x = ending_position_.x;
      }
      if (std::abs(current_position_.y - ending_position_.y) < kCardPathDelta) {
        current_position_.y = ending_position_.y;
      }

      //Else, move current position closer to end position
      if (current_position_.x > ending_position_.x) {
        current_position_.x -= kCardPathDelta;
      } else if (current_position_.x < ending_position_.x) {
        current_position_.x += kCardPathDelta;
      }
      if (current_position_.y > ending_position_.y) {
        current_position_.y -= kCardPathDelta;
      } else if (current_position_.y < ending_position_.y) {
        current_position_.y += kCardPathDelta;
      }

      cinder::gl::pushModelView();
      //Translate to the new current position
      cinder::gl::translate(current_position_);
      //Rotate
      if (should_rotate_) {
        cinder::gl::rotate(float(elapsed_seconds_ * kCardRotationSpeed));
      }
      //Translate so that rotation is around the middle of the card
      cinder::gl::translate(-kCardImageHalfWidth, -kCardImageHalfLength);
      cinder::gl::draw(card_texture_);
      cinder::gl::popModelView();
    }
  }
}

bool CardDrawer::ReachedEndPosition() {
  return current_position_ == ending_position_;
}
bool CardDrawer::Draws() {
  return should_draw_;
}

}