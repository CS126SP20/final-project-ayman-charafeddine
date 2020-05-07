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
  game_engine_ = GameEngine();
  current_trick_drawers_ = vector<CardDrawer>(4);
  trick_discarding_drawers_ = vector<CardDrawer>(4);
  state_ = GameState::SetUpGame;
  stats_ = vector<GameEngine::PlayerStats>(4);
}

void CardTableApp::setup() {
  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();
  ImGui::Initialize();

  //Setup all strategies
  for (size_t i = 0; i < kNumPlayers - 1; i++) {
    PlayerStrategy *strategy = new BasicPlayerStrategy();
    strategies_.push_back(strategy);
  }

}

void CardTableApp::update() {

  if (game_engine_.IsGameOver()) {
    EndGame();

  } else if (state_ == GameState::SetUpGame) {
    StartGame();

  } else if (game_engine_.IsRoundOver() && state_ != GameState::SetUpRound) {
    EndRound();

  } else if (state_ == GameState::SetUpRound) {
    StartRound();

  } else if (hands_drawer_.DealingComplete()) {
    RunRound();
  }

}

void CardTableApp::draw() {
  cinder::gl::clear(Color(0.04f, 0.42f, 0));

  hands_drawer_.UpdateAndDraw(getElapsedSeconds());

  for (auto &drawer : current_trick_drawers_) {
    drawer.UpdateAndDraw(getElapsedSeconds());
  }
  for (auto &drawer : trick_discarding_drawers_) {
    drawer.UpdateAndDraw(getElapsedSeconds());
  }
}

void CardTableApp::keyDown(KeyEvent event) {}

CardTableApp::~CardTableApp() {
  for (const auto &strategy : strategies_) {
    delete strategy;
  }
}

void CardTableApp::mouseDown(cinder::app::MouseEvent event) {
  if (game_engine_.GetCurrentPlayerIndex() == kHumanPlayerIndex
      && event.isLeftDown()
      && user_hand_rect_.contains(event.getPos())) {
    //Initialize card as an invalid one
    Card card_to_play_{Suit::kNumSuits, Rank::kNumRanks};
    size_t card_index_ = 0;
    //Exception case for first card to the right because the full card is showing
    if (event.getX() > kFirstCardBottomPlayer.x
        && event.getX() < kFirstCardBottomPlayer.x + 2 * kCardImageHalfWidth) {
      card_index_ = 0;
    } else {
      //Fancy formula to get card index based on click.
      card_index_ = (size_t) ((-event.getX() + 150) / 37 + 12);
    }
    card_to_play_ = user_hand_[card_index_];
    if (game_engine_.IsValidCard(card_to_play_)) {
      //Draw card being thrown
      current_trick_drawers_[kHumanPlayerIndex] =
          CardDrawer(kFirstCardBottomPlayer, kCardThrowingEndPositions[kHumanPlayerIndex], card_to_play_, true);
      hands_drawer_.RemoveCard(kHumanPlayerIndex, card_index_);
      //Don't delete card from user_hand_, in case user clicks in the card's former spot.
      game_engine_.HandleCard(card_to_play_);
    }
  }
}

void CardTableApp::StartRound() {
  current_trick_drawers_ = vector<CardDrawer>(4);
  trick_discarding_drawers_ = vector<CardDrawer>(4);

  Deck deck;
  vector<vector<Card>> cards_dealt_ = game_engine_.DealCards(deck);

  for (size_t i = 0; i < kNumPlayers - 1; i++) {
    strategies_[i]->receiveInitialCards(cards_dealt_[i]);
  }

  user_hand_ = cards_dealt_[3];
  //sort by rank
  std::stable_sort(user_hand_.begin(), user_hand_.end(), Card::CompareRanks);
  //sort by suit
  std::stable_sort(user_hand_.begin(), user_hand_.end(), Card::CompareSuits);
  hands_drawer_ = HandDrawer(user_hand_);
  state_ = GameState::RunGame;
}

void CardTableApp::RunRound() {
  const auto time = std::chrono::system_clock::now();
  Trick trick_ = game_engine_.GetCurrentTrick();
  size_t current_player_index_ = game_engine_.GetCurrentPlayerIndex();

  if (time < time_since_card_played + std::chrono::milliseconds(800)) {
    return;
  }

  if (trick_.TrickFinished() && current_trick_drawers_[current_player_index_].ReachedEndPosition()
      ) { //kNumSuits is the current suit at construction of game engine,
    // so this runs as long as a player has played
    for (size_t i = 0; i < kNumPlayers; i++) {
      trick_discarding_drawers_[i] = CardDrawer(kCardThrowingEndPositions[i],
                                                kOutsideOfWindowPositions[trick_.GetTrickEater()],
                                                trick_.GetCards()[i], false);
    }
    //empty trick drawers
    current_trick_drawers_ = vector<CardDrawer>(kNumPlayers);
    //tell game engine that trick has ended
    game_engine_.HandleEndOfTrick();

  } else if (current_player_index_ != kHumanPlayerIndex) {
    PlayerStrategy *current_strategy_ = strategies_[current_player_index_];
    //Get card from strategy
    Card card_to_play_ = current_strategy_->playCard(game_engine_.GetCurrentTrick().GetCards());
    //Keep trying while game engine says it's not a valid card to play
    while (!game_engine_.IsValidCard(card_to_play_)) {
      current_strategy_->receiveMoveValidation(false);
      card_to_play_ = current_strategy_->playCard(game_engine_.GetCurrentTrick().GetCards());
    }
    //Once the card chosen by strategy is valid, tell them
    current_strategy_->receiveMoveValidation(true);
    //Draw card being thrown
    current_trick_drawers_[current_player_index_] =
        CardDrawer(kPlayerPositions[current_player_index_],
                   kCardThrowingEndPositions[current_player_index_], card_to_play_, true);
    //Update time since last card was played
    time_since_card_played = time;
    //Remove card from hand
    hands_drawer_.RemoveCard(current_player_index_, 0);
    game_engine_.HandleCard(card_to_play_);
  }
}
void CardTableApp::StartGame() {
  ImGui::Begin("Likha", reinterpret_cast<bool *>(false), ImGuiWindowFlags_Modal);
  ImGui::Text("Your team mate : Player1 \nYour opponents : Player0 and Player2 \nEnter your name: ");
  ImGui::InputText("", &name_);
  if (!name_.empty()) {
    if (ImGui::Button("Start Game")) {
      StartRound();
    }
  }
  ImGui::End();
}
void CardTableApp::EndRound() {
  stats_ = game_engine_.GetPlayerStats();

  ImGui::Begin("Likha", reinterpret_cast<bool *>(false), ImGuiWindowFlags_Modal);
  std::stringstream scores;
  scores << "Team 0 :\nPlayer0: " << stats_[0].score_ << "\nPlayer2: "
         << stats_[2].score_ << "\n\nTeam 1 :\nPlayer1: " << stats_[1].score_ << "\n" << name_ << ": "
         << stats_[3].score_;
  ImGui::Text("%s", scores.str().c_str());
  if (ImGui::Button("Start Next Round")) {
    StartRound();
  }
  ImGui::End();
}
void CardTableApp::EndGame() {
  cinder::gl::clear(Color(0, 0, 0));

  ImGui::Begin("Likha", reinterpret_cast<bool *>(false), ImGuiWindowFlags_Modal);
  size_t losing_team_ = game_engine_.GetLosingTeam();
  size_t winning_team_ = (losing_team_ + 1) % 2; //1 if losing team is 0 and 0 if losing team if 1

  std::stringstream game_stats_;
  game_stats_ << "Game Over!\nWinners: Team " << winning_team_ << "\nLosers: Team " << losing_team_;

  ImGui::Text("%s", game_stats_.str().c_str());

  ImGui::End();

}

}  // namespace gui

} //namespace likha
