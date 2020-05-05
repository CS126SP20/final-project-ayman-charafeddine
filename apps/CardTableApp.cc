// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "CardTableApp.h"
#include "likha/HandDrawer.h"

#include <cinder/app/App.h>
#include <cinder/Font.h>
#include <cinder/Text.h>
#include <cinder/Vector.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>

#include <cinder/CinderImGui.h>
#include <likha/BasicPlayerStrategy.h>

#include <cmath>

namespace likha {

namespace gui {

using cinder::app::KeyEvent;
using cinder::loadImage;
using cinder::Color;

using Suit = likha::Card::Suit;
using Rank = likha::Card::Rank;

CardTableApp::CardTableApp() {
  state_ = GameState::Dealing;
  game_engine_ = GameEngine();
  current_trick_ = {};
  current_trick_drawers_ = vector<CardDrawer> (4);
}

void CardTableApp::setup() {
  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();
  ImGui::Initialize();

  for (size_t i = 0; i < kNumPlayers - 1; i++) {
    PlayerStrategy* strategy = new BasicPlayerStrategy();
    strategies_.push_back(strategy);
  }

  Deck deck;
  vector<vector<Card>> cards_dealt_ = game_engine_.DealCards(deck);

  for (size_t i = 0; i < kNumPlayers - 1; i++) {
    strategies_[i]->receiveInitialCards(cards_dealt_[i]);
  }

  hand_ = cards_dealt_[3];
  dealer_ = HandDrawer(cards_dealt_[3]);
}

void CardTableApp::update() {

  if (dealer_.DealingComplete() && current_trick_.empty()) {
    state_ = GameState::TrickTaking;
  }

  if (current_trick_drawers_[game_engine_.GetCurrentPlayerIndex() -1].ReachedEndPosition()) {
    state_ = GameState::TrickTaking;
  }

  if (state_ == GameState::TrickTaking) {
    if (game_engine_.GetCurrentPlayerIndex() != kHumanPlayerIndex) {
      PlayerStrategy* current_strategy_ = strategies_[game_engine_.GetCurrentPlayerIndex()];
      //Get card from strategy
      Card card_to_play_ = current_strategy_->playCard(current_trick_);
      //Keep trying while game engine says it's not a valid card to play
      while (!game_engine_.HandleAndValidateCard(card_to_play_)) {
        current_strategy_->receiveMoveValidation(false);
        card_to_play_ = current_strategy_->playCard(current_trick_);
      }
      //Once the card chosen by strategy is valid, tell them
      current_strategy_->receiveMoveValidation(true);
      //Add card to trick
      current_trick_.push_back(card_to_play_);
      current_trick_drawers_[game_engine_.GetCurrentPlayerIndex() - 1] =
          CardDrawer(GetPositionFromPlayerIndex(game_engine_.GetCurrentPlayerIndex() - 1),
              kCardThrowingEndPositions[game_engine_.GetCurrentPlayerIndex() -1],
              card_to_play_);
      state_ = GameState::DrawingCardPlayed;
      }
  }
}

void CardTableApp::draw() {
  cinder::gl::clear(Color(0.04f, 0.42f, 0));

  dealer_.UpdateAndDraw(getElapsedSeconds());

  if (dealer_.DealingComplete()) {
    for (auto &drawer : current_trick_drawers_) {
      drawer.UpdateAndDraw(getElapsedSeconds());
    }
  }
}

void CardTableApp::keyDown(KeyEvent event) {}

CardTableApp::~CardTableApp() {
  for (const auto& strategy : strategies_) {
    delete strategy;
  }
}

cinder::vec2 CardTableApp::GetPositionFromPlayerIndex(size_t player_index) {
  if (player_index == 0) {
    return kFirstCardLeftPlayer;
  } else if (player_index == 1) {
    return kFirstCardTopPlayer;
  } else if (player_index == 2) {
    return kFirstCardRightPlayer;
  } else if (player_index == 3) {
    return kFirstCardBottomPlayer;
  }
}

void CardTableApp::mouseDown(cinder::app::MouseEvent event) {
  if (game_engine_.GetCurrentPlayerIndex() == kHumanPlayerIndex) {
    if (event.isLeftDown() && user_hand_rect_.contains(event.getPos())) {
      if (event.getX() > 600 && event.getX() < 675) {
        current_trick_drawers_[kHumanPlayerIndex] = CardDrawer(kFirstCardBottomPlayer, kCardThrowingEndPositions[kHumanPlayerIndex], hand_[0]);
      } else {
        int card_index_ = (int) (-event.getX() + 150) / 37 + 12;
        current_trick_drawers_[kHumanPlayerIndex] =
            CardDrawer(kFirstCardBottomPlayer, kCardThrowingEndPositions[kHumanPlayerIndex], hand_[card_index_]);
      }
    }
  }
}

}  // namespace gui

} //namespace likha
