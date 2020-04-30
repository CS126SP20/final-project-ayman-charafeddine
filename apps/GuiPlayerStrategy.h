// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/gl/Texture.h>
#include <likha/PlayerStartegy.h>

namespace gui {

using namespace likha;

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
  void DrawDealing();
  cinder::gl::TextureRef card_texture_;
  bool gl_is_rotated_;
  float card_pos_change_;
  size_t cards_dealt_;
};

}  // namespace gui

#endif  // FINALPROJECT_APPS_MYAPP_H_
