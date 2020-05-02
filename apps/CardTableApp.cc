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

}

void CardTableApp::update() {
  if (state_ == GameState::TrickPlaying) {
    if (game_engine_.GetCurrentPlayerIndex() != kHumanPlayerIndex) {
      Card card_to_play_ = strategies_[game_engine_.GetCurrentPlayerIndex()]
          ->playCard(current_trick_);
      game_engine_.handlePlayedCard(card_to_play_);

    }
  }

}

void CardTableApp::draw() {
  cinder::gl::clear(Color(0.04f, 0.42f, 0));
  if (state_ == GameState::Dealing) {
    dealer_.Update(getElapsedSeconds());
  } else {
    DrawHand();
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

}  // namespace gui

} //namespace likha
