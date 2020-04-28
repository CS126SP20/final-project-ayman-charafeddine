//
// Created by ayman on 4/26/20.
//

#include <catch2/catch.hpp>
#include <likha/BasicPlayerStrategy.h>
#include <likha/GameEngine.h>

using namespace likha;

TEST_CASE("test constructor") {
  vector<PlayerStrategy*> players;
  for (size_t i = 0; i < kNumPlayers; i++) {
    players.push_back(new BasicPlayerStrategy());
  }
  GameEngine game_engine_(players);

  SECTION("test teams are correct") {
    SECTION("player 0") {
      REQUIRE(game_engine_.players_[0].team_ == 0);
    }
    SECTION("player 1") {
      REQUIRE(game_engine_.players_[1].team_ == 0);
    }
    SECTION("player 2") {
      REQUIRE(game_engine_.players_[2].team_ == 1);
    }
    SECTION("player 3") {
      REQUIRE(game_engine_.players_[3].team_ == 1);
    }
  }

  SECTION("test that strategies are all BasicPlayerStrategies") {
    for (size_t i = 0; i < kNumPlayers; i++) {
      REQUIRE(dynamic_cast<BasicPlayerStrategy*>(game_engine_.players_[i].strategy_ptr_) != nullptr);
    }
  }

  SECTION("test all scores begin at 0") {
    for (size_t i = 0; i < kNumPlayers; i++) {
      REQUIRE(game_engine_.players_[i].score_ == 0);
    }
  }

  SECTION("Test names were properly initialized (not empty string)") {
    for (size_t i = 0; i < kNumPlayers; i++) {
      REQUIRE(game_engine_.players_[i].name_ != "");
    }
  }
}