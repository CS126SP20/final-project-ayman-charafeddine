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
  dealer_ = Dealer(PlayerPosition::kNumPlayers, getWindowCenter(), getElapsedSeconds());
  state_ = GameState::Dealing;

}

void GuiPlayerStrategy::setup() {
  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();
  ImGui::Initialize();
  Deck deck;
  for (size_t i = 0; i < kNumCardsPerPlayer; i++) {
    hand_.push_back(deck.Draw());
  }
}

void GuiPlayerStrategy::update() {
  if (dealer_.DealingComplete()) {
    state_ = GameState::Gifting;
  }

}

void GuiPlayerStrategy::draw() {
  cinder::gl::clear(Color(0.04f, 0.42f, 0));
  if (state_ == GameState::Dealing) {
    dealer_.Update(getElapsedSeconds());
  } else {
    DrawHand();
  }
}

void GuiPlayerStrategy::keyDown(KeyEvent event) { }

string GuiPlayerStrategy::chooseName() const {

}
void GuiPlayerStrategy::receiveNames(string teammate_name_, vector<string> opponent_names_) {

}
void GuiPlayerStrategy::receiveInitialCards(vector<Card> cards) {
  hand_ = cards;
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
void GuiPlayerStrategy::DrawHand() {
  float x_position_ = getWindowCenter().x + 5 * kImageHalfWidth;
  for (const auto& card : hand_) {
    cinder::gl::TextureRef card_texture_ = cinder::gl::Texture::create(loadImage(Dealer::GetCardImagePath(card)));
    cinder::gl::draw(card_texture_, {x_position_, kBottomOfWindow - kImageHalfLength * 2});
    x_position_ -= kImageHalfWidth;
  }

}

}  // namespace gui
