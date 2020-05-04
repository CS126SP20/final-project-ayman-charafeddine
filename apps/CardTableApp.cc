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
  state_ = GameState::TrickTaking;
  game_engine_ = GameEngine();
  current_trick_index_ = 0;
  current_player_index_ = 0;
  current_trick_ = {};
}

void CardTableApp::setup() {
//  cinder::gl::enableDepthWrite();
//  cinder::gl::enableDepthRead();
//  ImGui::Initialize();
//
//  for (size_t i = 0; i < kNumPlayers - 1; i++) {
//    PlayerStrategy* strategy = new BasicPlayerStrategy();
//    strategies_.push_back(strategy);
//  }
//
  Deck deck;
  current_player_index_ = game_engine_.GetCurrentPlayerIndex();
  vector<vector<Card>> cards_dealt_ = game_engine_.DealCards(deck);
//
//  for (size_t i = 0; i < kNumPlayers - 1; i++) {
//    strategies_[i]->receiveInitialCards(cards_dealt_[i]);
//  }
//
//  hand_ = cards_dealt_[3];
  dealer_ = Dealer(cards_dealt_[3]);
}

void CardTableApp::update() {
  dealer_.Update(getElapsedSeconds());

//  if (current_trick_.empty() || current_trick_[current_trick_index_].HasCardBeenDrawn()) {
//    state_ = GameState::TrickTaking;
//  }
//
//  if (state_ == GameState::TrickTaking) {
//    PlayerStrategy* current_strategy_ = strategies_[current_player_index_];
//
//    if (current_player_index_ != kHumanPlayerIndex) {
//      Card card_to_play_ = current_strategy_->playCard(current_trick_);
//      while (!game_engine_.HandleAndValidateCard(card_to_play_)) {
//        current_strategy_->receiveMoveValidation(false);
//        card_to_play_ = current_strategy_->playCard(current_trick_);
//      }
//      current_strategy_->receiveMoveValidation(true);
//      if (current_trick_index_ > 0) {
//        current_trick_index_++;
//      }
//      current_trick_.push_back(card_to_play_);
//      current_player_index_ = (current_player_index_ + 1) % kNumPlayers;
//      state_ = GameState::DrawingCardPlayed;
//      }
//  }
}

void CardTableApp::draw() {
//  cinder::gl::clear(Color(0.04f, 0.42f, 0));
//  if (state_ == GameState::Dealing) {
//    dealer_.Update(getElapsedSeconds());
//  } else {
//    //DrawHand();
//    if (state_ == GameState::DrawingCardPlayed) {
//      current_trick_[current_trick_index_].DrawCardPlayed(current_player_index_, getWindowCenter(), getElapsedSeconds());
//    }
//  }
}

void CardTableApp::keyDown(KeyEvent event) {}

void CardTableApp::DrawHand() {
  float x_position_ = getWindowCenter().x + 6 * kCardImageHalfWidth;
  for (const auto &card : hand_) {
    cinder::gl::TextureRef card_texture_ = cinder::gl::Texture::create(loadImage(card.GetCardImagePath()));
    cinder::gl::draw(card_texture_, {x_position_, kBottomOfWindow - kCardImageHalfLength * 2});
    x_position_ -= kCardImageHalfWidth;
  }
}


CardTableApp::~CardTableApp() {
  for (const auto& strategy : strategies_) {
    delete strategy;
  }
}

}  // namespace gui

} //namespace likha
