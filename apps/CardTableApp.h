// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/gl/Texture.h>
#include <likha/PlayerStartegy.h>
#include "likha/HandDrawer.h"
#include <likha/GameEngine.h>

namespace likha {

namespace gui {

static constexpr size_t kHumanPlayerIndex = 3;
static const vector<cinder::vec2> kCardThrowingEndPositions = {{320, 400}, {400, 320},
                                                               {480, 400}, {400, 480}};
static const cinder::Rectf user_hand_rect_ = {150, kFirstCardBottomPlayer.y,660,800};
static const vector<cinder::vec2> kOutsideOfWindowPositions = {{- 200, 400}, {400, -200},
                                                               {1000, 400}, {400, 1000}};

enum class GameState {
  StartGame,
  StartRound,
  Dealing,
  Gifting,
  TakingTricks,
  EndRound,
  EndGame,
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
  void BeginRound();
  void RunRound();
  GameState state_;
  HandDrawer hands_drawer_;
  vector<Card> user_hand_;
  GameEngine game_engine_;
  vector<PlayerStrategy*> strategies_;
  vector<CardDrawer> current_trick_drawers_;
  std::chrono::time_point<std::chrono::system_clock> time_since_card_played;
  vector<CardDrawer> trick_discarding_drawers_;
  vector<GameEngine::PlayerStats> stats_;
  string name_;

  template<typename C>
  void PrintText(const string &text, const C &color, const glm::ivec2 &size, const vec2 &loc);
  void DrawScores();
};

}  // namespace gui

} // namespace likha
#endif  // FINALPROJECT_APPS_MYAPP_H_
