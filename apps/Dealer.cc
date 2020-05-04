//
// Created by ayman on 4/29/20.
//

#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <cinder/ImageIo.h>
#include "Dealer.h"

namespace likha {

namespace gui {

using cinder::loadImage;
using cinder::Color;

Dealer::Dealer(vector<Card> hand_) {
  for (size_t i = 0; i < kNumCardsPerPlayer; i++) {
    card_drawers_ = vector<vector<CardDrawer>> (4, vector<CardDrawer>());
    CardDrawer left_card_(kCenter,{kFirstCardLeftPlayer.x, kFirstCardLeftPlayer.y + kCardImageHalfWidth * i});
    CardDrawer top_card_(kCenter, {kFirstCardTopPlayer.x + kCardImageHalfWidth * i, kFirstCardTopPlayer.y});
    CardDrawer right_card_(kCenter, {kFirstCardRightPlayer.x, kFirstCardRightPlayer.y + kCardImageHalfWidth * i});
    card_drawers_[0].push_back(left_card_);
    card_drawers_[1].push_back(top_card_);
    card_drawers_[2].push_back(right_card_);
  }
  for (size_t i = 0; i < kNumCardsPerPlayer; i++) {
    CardDrawer user_card_(kCenter, {kFirstCardBottomPlayer.x + kCardImageHalfWidth * i, kFirstCardBottomPlayer.y}, hand_[i]);
    card_drawers_[3].push_back(user_card_);
  }
}

Dealer::Dealer() = default;

void Dealer::Update(double new_elapsed_seconds_) {
  for (size_t i = 0; i < kNumCardsPerPlayer; i++) {
    for (size_t j = 0; j < kNumPlayers; j++) {
      card_drawers_[j][i].UpdateAndDraw(new_elapsed_seconds_);
    }
  }
}

bool Dealer::DealingComplete() {
  for (size_t i = 0; i < kNumCardsPerPlayer; i++) {
    for (size_t j = 0; j < kNumPlayers; j++) {
      if (!card_drawers_[j][i].ReachedEndPosition()) {
        return false;
      }
    }
  }
  return true;
}

}

}