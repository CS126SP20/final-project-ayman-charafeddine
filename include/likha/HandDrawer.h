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
  HandDrawer(vector<Card> hand_);
  HandDrawer();
  void UpdateAndDraw(double new_elapsed_seconds_);
  void RemoveCard(size_t player_index_, size_t card_index_);
  bool DealingComplete();
 private:
  vector<vector<CardDrawer>> card_drawers_;

};

}

}
#endif //FINALPROJECT_INCLUDE_LIKHA_HANDDRAWER_H_
