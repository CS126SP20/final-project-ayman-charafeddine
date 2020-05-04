//
// Created by ayman on 4/29/20.
//

#ifndef FINALPROJECT_APPS_DEALER_H_
#define FINALPROJECT_APPS_DEALER_H_

#include <likha/GameEngine.h>
#include <cinder/gl/Texture.h>
#include <likha/CardDrawer.h>

namespace likha {

namespace gui {

static const cinder::vec2 kCenter = {400, 400};
static const cinder::vec2 kFirstCardLeftPlayer = {0, 150};
static const cinder::vec2 kFirstCardTopPlayer = {150, 0};
static const cinder::vec2 kFirstCardRightPlayer = {800 - kCardImageHalfWidth * 2, 150};
static const cinder::vec2 kFirstCardBottomPlayer = {150, 800 - kCardImageHalfLength * 2};

class Dealer {
 public:
  Dealer(vector<Card> hand_);
  Dealer();
  void Update(double new_elapsed_seconds_);
  bool DealingComplete();
 private:
  size_t cards_dealt_;
  vector<vector<CardDrawer>> card_drawers_;

};

}

}
#endif //FINALPROJECT_APPS_DEALER_H_
