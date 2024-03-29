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
  SetUpGame,
  SetUpRound,
  RunGame
};

class CardTableApp : public cinder::app::App {
 public:
  //cinder functions
  CardTableApp();
  void setup() override;
  void update() override;
  void draw() override;
  void mouseDown(cinder::app::MouseEvent event) override;
  ~CardTableApp() override;

 private:

  GameState state_;
  HandDrawer hands_drawer_;

  /**Cards in user's posetion. Does not delete when player plays a card*/
  vector<Card> user_hand_;

  GameEngine game_engine_;
  vector<PlayerStrategy*> strategies_;

  /** CardDrawers for the current trick*/
  vector<CardDrawer> current_trick_drawers_;

  std::chrono::time_point<std::chrono::system_clock> time_since_card_played;

  /** Card Drawers for the current trick being discarded at the end of a trick.*/
  vector<CardDrawer> trick_discarding_drawers_;

  vector<GameEngine::PlayerStats> stats_;
  string name_;

  /**
   * Set up a new Game.
   */
  void StartGame();
  /**
   * Draw the scores at the end of a round.
   */
  void EndRound();
  /** Give winning team at the end of a game*/
  void EndGame();
  /**
  * Set up the new round.
  */
  void StartRound();
  /**
   * Let strategies play their cards.
   */
  void RunRound();
};

}  // namespace gui

} // namespace likha
#endif  // FINALPROJECT_APPS_MYAPP_H_
