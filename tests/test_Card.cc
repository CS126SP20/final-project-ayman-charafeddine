// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <likha/Card.h>

using namespace likha;
using Suit = likha::Card::Suit;
using Rank = likha::Card::Rank;

TEST_CASE("Test GetRank() and GetSuit()") {
  Card ace_of_spades_(Suit::Spades, Rank::Ace);
  Card two_of_hearts_(Suit::Hearts, Rank::Two);
  Card jack_of_clubs_(Suit::Clubs, Rank::Jack);
  Card king_of_diamonds_(Suit::Diamonds, Rank::King);

  SECTION("Test GetRank()") {
    SECTION("Test Ace") {
      REQUIRE(ace_of_spades_.GetRank() == Rank::Ace);
    }

    SECTION("Test Two") {
      REQUIRE(two_of_hearts_.GetRank() == Rank::Two);
    }

    SECTION("Test Jack") {
      REQUIRE(jack_of_clubs_.GetRank() == Rank::Jack);
    }

    SECTION("Test King") {
      REQUIRE(king_of_diamonds_.GetRank() == Rank::King);
    }
  }

  SECTION("Test GetSuit()") {
    SECTION("Test Spades") {
      REQUIRE(ace_of_spades_.GetSuit() == Suit::Spades);
    }

    SECTION("Test Hearts") {
      REQUIRE(two_of_hearts_.GetSuit() == Suit::Hearts);
    }

    SECTION("Test Clubs") {
      REQUIRE(jack_of_clubs_.GetSuit() == Suit::Clubs);
    }

    SECTION("Test Diamonds") {
      REQUIRE(king_of_diamonds_.GetSuit() == Suit::Diamonds);
    }
  }
}

TEST_CASE("Test GetPointValue()") {
  SECTION("Test Hearts point value") {
    SECTION("Test Two of Hearts point value") {
      Card two_of_hearts_(Suit::Hearts, Rank::Two);
      REQUIRE(two_of_hearts_.GetPointValue() == kHeartsValue);
    }

    SECTION("Test Ace of Hearts point value") {
      Card ace_of_hearts_(Suit::Hearts, Rank::Ace);
      REQUIRE(ace_of_hearts_.GetPointValue() == kHeartsValue);
    }

    SECTION("Test Queen of Hearts point value") {
      Card queen_of_hearts_(Suit::Hearts, Rank::Queen);
      REQUIRE(queen_of_hearts_.GetPointValue() == kHeartsValue);
    }
  }

  SECTION("Test likhas point value") {
    SECTION("Test Queen of Spades point value") {
      Card queen_of_spades_(Suit::Spades, Rank::Queen);
      REQUIRE(queen_of_spades_.GetPointValue() == kQueenSpadesValue);
    }

    SECTION("Test Ten of Diamonds point value") {
      Card ten_of_diamonds_(Suit::Diamonds, Rank::Ten);
      REQUIRE(ten_of_diamonds_.GetPointValue() == kTenDiamondsValue);
    }
  }

  SECTION("Test no value cards") {
    SECTION("Test CLub point value") {
      Card jack_of_clubs_(Suit::Clubs, Rank::Jack);
      REQUIRE(jack_of_clubs_.GetPointValue() == kNoValue);
    }

    SECTION("Test non-likha Spade") {
      Card seven_of_spades_(Suit::Spades, Rank::Seven);
      REQUIRE(seven_of_spades_.GetPointValue() == kNoValue);
    }

    SECTION("Test non-likha Diamond") {
      Card king_of_diamonds_(Suit::Diamonds, Rank::King);
      REQUIRE(king_of_diamonds_.GetPointValue() == kNoValue);
    }
  }
}