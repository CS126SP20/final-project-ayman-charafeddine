// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/gl/Texture.h>
#include <likha/PlayerStartegy.h>
#include "likha/HandDrawer.h"

namespace likha {

namespace gui {

static constexpr size_t kHumanPlayerIndex = 3;
static const vector<cinder::vec2> kCardThrowingEndPositions = {{320, 400}, {400, 320},
                                                               {480, 400}, {400, 480}};
static const cinder::Rectf user_hand_rect_ = {150,
                                                    kFirstCardBottomPlayer.y,
                                                    660,
                                                    800};

enum class GameState {
  SetUp,
  Dealing,
  Gifting,
  TrickTaking,
  DrawingCardPlayed
};

class CardTableApp : public cinder::app::App {
 public:
  //cinder functions
  CardTableApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  void mouseDown(cinder::app::MouseEvent event) override;
  ~CardTableApp() override;

 private:
  GameState state_;
  HandDrawer dealer_;
  vector<Card> hand_;
  GameEngine game_engine_;
  vector<PlayerStrategy*> strategies_;
  vector<CardDrawer> current_trick_drawers_;
  std::chrono::time_point<std::chrono::system_clock> time_since_card_played;
};

}  // namespace gui

} // namespace likha
#endif  // FINALPROJECT_APPS_MYAPP_H_
