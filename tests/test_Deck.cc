//
// Created by ayman on 4/18/20.
//

#include <catch2/catch.hpp>

#include <likha/Deck.h>
#include <likha/Card.h>

using namespace likha;
using Suit = likha::Card::Suit;
using Rank = likha::Card::Rank;

TEST_CASE("Test Draw() function") {
  Deck deck;
  SECTION("Test starting size") {
    REQUIRE(deck.size() == kDeckSize);
  }
  Card card = deck.Draw();
  SECTION("Test Card drawn has valid suit") {
    REQUIRE((card.GetSuit() >= Suit::Diamonds && card.GetSuit() <= Suit::Clubs));
  }
  SECTION("Test card has valid rank") {
    REQUIRE((card.GetRank() >= Rank::Two && card.GetRank() <= Rank::Ace));
  }
  SECTION("Test card was removed") {
    REQUIRE(deck.size() == kDeckSize - 1);
  }
}