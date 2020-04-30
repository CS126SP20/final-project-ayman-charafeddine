// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "GuiPlayerStrategy.h"
#include "Dealer.h"

#include <cinder/app/App.h>
#include <cinder/Font.h>
#include <cinder/Text.h>
#include <cinder/Vector.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>

#include <cinder/CinderImGui.h>




namespace gui {

using cinder::app::KeyEvent;
using cinder::loadImage;
using cinder::Color;

using Suit = likha::Card::Suit;
using Rank = likha::Card::Rank;

GuiPlayerStrategy::GuiPlayerStrategy() {
}

void GuiPlayerStrategy::setup() {
  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();
  ImGui::Initialize();
  dealer_ = Dealer(PlayerPosition::kNumPlayers, getWindowCenter(), getElapsedSeconds());
  state_ = GameState::Dealing;
}

void GuiPlayerStrategy::update() {

}

void GuiPlayerStrategy::draw() {
  cinder::gl::clear(Color(0.04f, 0.42f, 0));
  if (state_ == GameState::Dealing) {
    dealer_.Update(getElapsedSeconds());
  }
}

void GuiPlayerStrategy::keyDown(KeyEvent event) { }

string GuiPlayerStrategy::chooseName() const {
  return std::__cxx11::string();
}
void GuiPlayerStrategy::receiveNames(string teammate_name_, vector<string> opponent_names_) {

}
void GuiPlayerStrategy::receiveInitialCards(vector<Card> cards) {

}
vector<Card> GuiPlayerStrategy::giftCards() {
  return vector<Card>({Card(Suit::Hearts, Rank::Six)});
}
void GuiPlayerStrategy::receiveGift(vector<Card> cards) {

}
Card GuiPlayerStrategy::playCard(vector<Card> cardsPlayed) {
  return Card(Suit::Hearts, Rank::Six);
}
void GuiPlayerStrategy::receiveMoveValidation(string) {

}
void GuiPlayerStrategy::receiveCurrentScores(map<string, size_t> currentScores) {

}

}  // namespace gui
