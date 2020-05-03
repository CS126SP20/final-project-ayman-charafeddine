// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "CardTableApp.h"
#include "Dealer.h"

#include <cinder/app/App.h>
#include <cinder/Font.h>
#include <cinder/Text.h>
#include <cinder/Vector.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>

#include <cinder/CinderImGui.h>
#include <likha/BasicPlayerStrategy.h>

namespace likha {

namespace gui {

using cinder::app::KeyEvent;
using cinder::loadImage;
using cinder::Color;

using Suit = likha::Card::Suit;
using Rank = likha::Card::Rank;

CardTableApp::CardTableApp() {
  dealer_ = Dealer(PlayerPosition::kNumPlayers, getWindowCenter(), getElapsedSeconds());
  state_ = GameState::SetUp;
  game_engine_ = GameEngine();
}

void CardTableApp::setup() {
  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();
  ImGui::Initialize();

  for (size_t i = 0; i < kNumPlayers - 1; i++) {
    PlayerStrategy* strategy = new BasicPlayerStrategy();
    strategies_.push_back(strategy);
  }

  current_index_ = game_engine_.GetCurrentPlayerIndex();

}

void CardTableApp::update() {
  if (state_ == GameState::TrickPlaying) {
    PlayerStrategy* current_strategy_ = strategies_[current_index_];

    if (current_index_ != kHumanPlayerIndex) {
      Card card_to_play_ = current_strategy_->playCard(current_trick_);
      if (game_engine_.HandleAndValidateCard(card_to_play_)) {
        current_strategy_->receiveMoveValidation(true);
        current_trick_.push_back(card_to_play_);
        current_index_ = (current_index_ + 1) % kNumPlayers;
      } else {
        current_strategy_->receiveMoveValidation(false);
      }
    }
  }
}

void CardTableApp::draw() {
  cinder::gl::clear(Color(0.04f, 0.42f, 0));
  if (state_ == GameState::Dealing) {
    dealer_.Update(getElapsedSeconds());
  } else {
    DrawHand();
    if (current_index_ == kHumanPlayerIndex) {
      //input
    } else {
      DrawCardPlayed(current_trick_, current_index_);
    }
  }
}

void CardTableApp::keyDown(KeyEvent event) {}

void CardTableApp::DrawHand() {
  float x_position_ = getWindowCenter().x + 6 * kImageHalfWidth;
  for (const auto &card : hand_) {
    cinder::gl::TextureRef card_texture_ = cinder::gl::Texture::create(loadImage(Dealer::GetCardImagePath(card)));
    cinder::gl::draw(card_texture_, {x_position_, kBottomOfWindow - kImageHalfLength * 2});
    x_position_ -= kImageHalfWidth;
  }
}
void CardTableApp::DrawCardPlayed(vector<Card> current_trick_, size_t current_index_) {

}

}  // namespace gui

} //namespace likha
