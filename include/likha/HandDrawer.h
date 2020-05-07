//
// Created by ayman on 4/29/20.
//

#ifndef FINALPROJECT_INCLUDE_LIKHA_HANDDRAWER_H_
#define FINALPROJECT_INCLUDE_LIKHA_HANDDRAWER_H_

#include <likha/GameEngine.h>
#include <cinder/gl/Texture.h>
#include <likha/CardDrawer.h>

namespace likha {

namespace gui {

static const cinder::vec2 kCenter = {400, 400};
static const cinder::vec2 kFirstCardLeftPlayer = {1, 150};
static const cinder::vec2 kFirstCardTopPlayer = {150, 1};
static const cinder::vec2 kFirstCardRightPlayer = {800 - kCardImageHalfWidth * 2, 150};
static const cinder::vec2 kFirstCardBottomPlayer = {600, 800 - kCardImageHalfLength * 2};
static const vector<cinder::vec2> kPlayerPositions = {kFirstCardLeftPlayer, kFirstCardTopPlayer, kFirstCardRightPlayer, kFirstCardBottomPlayer};

class HandDrawer {
 public:
  /**
   * Constructor based on user hand.
   * @param hand_
   */
  HandDrawer(vector<Card> user_hand_);
  /**
   * Default constructor, doesn't draw anything when UpdateAndDraw is called.
   */
  HandDrawer();
  /**
   * Update positions and draw the hands in new positions.
   * @param new_elapsed_seconds_ seconds elapsed to be used for rotating
   */
  void UpdateAndDraw(double new_elapsed_seconds_);
  /**
   * Remove a card from hand. Removes the specific card if from human hand,
   * and the next card if from face-down computer hands.
   * @param player_index_
   * @param card_index_
   */
  void RemoveCard(size_t player_index_, size_t card_index_);
  /**
   * Return whether all cards are in their positions in the hand or whether theyr are still being dealt.
   */
  bool DealingComplete();

 private:
  /** Card drawer for each card in hands. */
  vector<vector<CardDrawer>> card_drawers_;

};

}

}
#endif //FINALPROJECT_INCLUDE_LIKHA_HANDDRAWER_H_
