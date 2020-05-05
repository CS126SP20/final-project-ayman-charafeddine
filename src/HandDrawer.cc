//
// Created by ayman on 4/29/20.
//

#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <cinder/ImageIo.h>
#include "likha/HandDrawer.h"
#include "../apps/CardTableApp.h"

namespace likha {

namespace gui {

using cinder::loadImage;
using cinder::Color;

HandDrawer::HandDrawer(vector<Card> hand_) {
  card_drawers_ = vector<vector<CardDrawer>> (4, vector<CardDrawer>());
  for (size_t i = 0; i < kNumCardsPerPlayer; i++) {
    CardDrawer left_card_(kCenter,{kFirstCardLeftPlayer.x, kFirstCardLeftPlayer.y + kCardImageHalfWidth * i});
    CardDrawer top_card_(kCenter, {kFirstCardTopPlayer.x + kCardImageHalfWidth * i, kFirstCardTopPlayer.y});
    CardDrawer right_card_(kCenter, {kFirstCardRightPlayer.x, kFirstCardRightPlayer.y + kCardImageHalfWidth * i});
    card_drawers_[0].push_back(left_card_);
    card_drawers_[1].push_back(top_card_);
    card_drawers_[2].push_back(right_card_);
  }
  for (size_t i = 0; i < kNumCardsPerPlayer; i++) {
    CardDrawer user_card_(kCenter, {kFirstCardBottomPlayer.x - kCardImageHalfWidth * i, kFirstCardBottomPlayer.y}, hand_[i]);
    card_drawers_[3].push_back(user_card_);
  }
}

HandDrawer::HandDrawer() = default;

void HandDrawer::UpdateAndDraw(double new_elapsed_seconds_) {
  for (size_t i = 0; i < kNumCardsPerPlayer; i++) {
    for (size_t j = 0; j < kNumPlayers; j++) {
      card_drawers_[j][i].UpdateAndDraw(new_elapsed_seconds_);
    }
  }
}

bool HandDrawer::DealingComplete() {
  for (size_t i = 0; i < kNumCardsPerPlayer; i++) {
    for (size_t j = 0; j < kNumPlayers; j++) {
      if (!card_drawers_[j][i].ReachedEndPosition()) {
        return false;
      }
    }
  }
  return true;
}

void HandDrawer::RemoveCard(size_t player_index_, size_t card_index_) {
  if (player_index_ == kHumanPlayerIndex) {
    card_drawers_[player_index_][card_index_] = CardDrawer();
  } else {
    for (auto& drawer_ : card_drawers_[player_index_]) {
      if (drawer_.Draws()) {
        drawer_ = CardDrawer();
        return;
      }
    }
  }
}

}

}