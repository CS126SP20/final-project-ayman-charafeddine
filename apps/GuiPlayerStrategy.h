// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/gl/Texture.h>
#include <likha/PlayerStartegy.h>
#include "Dealer.h"

namespace gui {

using namespace likha;

static constexpr float kBottomOfWindow = 780.0f;

enum class GameState {
  SetUp,
  Dealing,
  Gifting,
  TrickPlaying,
};

 class GuiPlayerStrategy : public cinder::app::App, public likha::PlayerStrategy {
 public:
   //cinder functions
   GuiPlayerStrategy();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  //PlayerStrategy functions
  string chooseName() const override;
  void receiveNames(string teammate_name_, vector<string> opponent_names_) override;
   void receiveInitialCards(vector<Card> cards) override;
   vector<Card> giftCards() override;
   void receiveGift(vector<Card> cards) override;
   Card playCard(vector<Card> cardsPlayed) override;
   void receiveMoveValidation(string) override;
   void receiveCurrentScores(map<string, size_t> currentScores) override;
   ~GuiPlayerStrategy() override = default;
 private:
   GameState state_;
   Dealer dealer_;
   vector<Card> hand_;
   void DrawHand();
};

}  // namespace gui

#endif  // FINALPROJECT_APPS_MYAPP_H_
