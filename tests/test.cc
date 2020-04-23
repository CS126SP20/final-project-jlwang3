// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <cinder/Rand.h>

#include <mylibrary/leaderboard.h>
#include <mylibrary/player.h>
#include <mylibrary/location.h>
#include <mylibrary/piece.h>
#include <vector>

TEST_CASE("Staying in Bounds") {

    mylibrary::Location origin_(0,0);
    mylibrary::Piece square_piece;
    SECTION("Bottom Left Corner") {
        REQUIRE(square_piece == square_piece.MoveDown());
    }
}