// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <cinder/Rand.h>

#include <mylibrary/leaderboard.h>
#include <mylibrary/player.h>
#include <mylibrary/location.h>
#include <mylibrary/piece.h>
#include <vector>

TEST_CASE("Location Operators") {
    mylibrary::Location origin(0,0);
    REQUIRE(origin + mylibrary::Location(1,1) == mylibrary::Location(1,1));
}