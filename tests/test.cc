// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <cinder/Rand.h>

#include <mylibrary/leaderboard.h>
#include <mylibrary/player.h>
#include <mylibrary/location.h>

mylibrary::Location origin_(0,0);

TEST_CASE("Staying in Bounds") {
    SECTION("Bottom Left") {
        mylibrary::Location loc_1(-1, -1);
        REQUIRE(origin_ == loc_1);
    }
    SECTION("Left Wall") {
        mylibrary::Location loc_2(-2, 5);
        REQUIRE(loc_2 == mylibrary::Location(0, 5));
    }
    SECTION("Top") {
        mylibrary::Location loc_3(8, 10);
        REQUIRE(loc_3 == mylibrary::Location(8, 9));
    }
}