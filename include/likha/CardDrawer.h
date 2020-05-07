//
// Created by ayman on 5/3/20.
//

#ifndef FINALPROJECT_INCLUDE_LIKHA_CARDDRAWER_H_
#define FINALPROJECT_INCLUDE_LIKHA_CARDDRAWER_H_

#include "Card.h"

namespace likha {

using cinder::vec2;

/**
 * Class in charge of drawing a card image moving along a path as well as drawing the card once it reaches its end position.
 */
class CardDrawer {
 public:
  /**
   * Default constructor, creates an object that doesn't draw anything.
   */
  CardDrawer();

  /**
   * Construct a CardDrawer for a specific card to be used for card throwing.
   */
  CardDrawer(const vec2 &start_position_, const vec2 &end_position_, Card card, bool rotate_);

  /**
   * Construct a CardDrawer for the back of the cards to be used for card dealing.
   */
  CardDrawer(const vec2 &start_position_, const vec2 &end_position_, bool rotate_);

  /**
   * UpdateAndDraw appropriate fields and draw the card.
   * @param elapsed_seconds_  elapsed seconds in app, used to rotate.
   */
  void UpdateAndDraw(double elapsed_seconds_);

  /**
   * Whether the card reached its end position. Used to know if next player should play.
   */
  bool ReachedEndPosition();

  /**
   * Whether the drawer draws anything.
   */
   bool Draws();

 private:
  vec2 starting_position_;
  vec2 ending_position_;
  cinder::gl::TextureRef card_texture_;
  vec2 current_position_;
  bool should_draw_;
  bool should_rotate_;

};
}



#endif //FINALPROJECT_INCLUDE_LIKHA_CARDDRAWER_H_
