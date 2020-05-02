// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/gl/Texture.h>
#include <likha/PlayerStartegy.h>
#include "Dealer.h"

namespace likha {

namespace gui {

static constexpr float kBottomOfWindow = 780.0f;
static constexpr size_t kHumanPlayerIndex = 3;

enum class GameState {
  SetUp,
  Dealing,
  Gifting,
  TrickPlaying,
};

class CardTableApp : public cinder::app::App {
 public:
  //cinder functions
  CardTableApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;

 private:
  GameState state_;
  Dealer dealer_;
  vector<Card> hand_;
  void DrawHand();
  GameEngine game_engine_;
  vector<PlayerStrategy *> strategies_;
  vector<Card> current_trick_;
};

}  // namespace gui

} // namespace likha
#endif  // FINALPROJECT_APPS_MYAPP_H_
