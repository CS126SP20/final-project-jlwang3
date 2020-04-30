// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <cinder/Rand.h>

#include <mylibrary/leaderboard.h>
#include <mylibrary/player.h>
#include <mylibrary/location.h>
#include <mylibrary/segment.h>
#include <mylibrary/piece.h>
#include <mylibrary/engine.h>
#include <vector>

/**
 * Testing Location.h
 */
TEST_CASE("Location Boolean Operators") {

    mylibrary::Location origin_(0,0);

    SECTION("Boolean Operator") {
        REQUIRE(origin_ == mylibrary::Location(0,0));
        REQUIRE(origin_ != mylibrary::Location(1,1));
    }
    SECTION("Less Than") {
        REQUIRE(origin_ < mylibrary::Location(1, 0));
        REQUIRE(origin_ <= origin_);
    }
    SECTION("Greater Than") {
        REQUIRE(mylibrary::Location(1,3) > origin_);
        REQUIRE(origin_ >= origin_);
    }
}

TEST_CASE("Location Vector Operators") {
    SECTION("Addition Operator") {
        REQUIRE(mylibrary::Location(0,0) + mylibrary::Location(1,1) == mylibrary::Location(1,1));
    }
    SECTION("Modulus Operator") {
        SECTION("1x1") {

            mylibrary::Location one_by_one_(1,1);

            for (int i = -9; i < 10; ++i) {
                for (int j = -9; j < 10; ++j) {
                    REQUIRE(mylibrary::Location(i,j) % one_by_one_ == mylibrary::Location(0,0));
                }
            }
        }
        REQUIRE(mylibrary::Location(5,11) % mylibrary::Location(2,1) == mylibrary::Location(1,0));
        REQUIRE(mylibrary::Location(5,11) % mylibrary::Location(2,13) == mylibrary::Location(1,11));
        REQUIRE(mylibrary::Location(11,11) % mylibrary::Location(6,3) == mylibrary::Location(5,2));
    }
    SECTION("Subtraction Operator") {
        REQUIRE(mylibrary::Location(0,0) - mylibrary::Location(1,1) == mylibrary::Location(-1,-1));
    }
}

TEST_CASE("Accessors") {
    mylibrary::Location first_accessor_ = mylibrary::Location(0,0) + mylibrary::Location(1,1);
    mylibrary::Location second_accessor_ = mylibrary::Location(0,0) - mylibrary::Location(1,1);
    mylibrary::Location third_accessor_ = mylibrary::Location(5,11) % mylibrary::Location(2,13);
    REQUIRE(first_accessor_.Row() == 1); REQUIRE(first_accessor_.Col() == 1);
    REQUIRE(second_accessor_.Row() == -1); REQUIRE(second_accessor_.Col() == -1);
    REQUIRE(third_accessor_.Row() == 1); REQUIRE(third_accessor_.Col() == 11);
}

/**
 * Testing Segment.h
 */
TEST_CASE("Getters and Setters") {

    mylibrary::Location origin_(0,0);
    mylibrary::Segment test_segment_ (origin_, mylibrary::blue);

    REQUIRE(test_segment_.GetLocation() == origin_);
    REQUIRE(test_segment_.GetColor() == mylibrary::blue);

    test_segment_.SetLocation(mylibrary::Location (-10,-3));
    test_segment_.SetColor(mylibrary::blue);

    REQUIRE(test_segment_.GetLocation() == mylibrary::Location(-10,-3));
    REQUIRE(test_segment_.GetColor() == mylibrary::blue);
}

/**
 * Testing Engine.h
 */
TEST_CASE("Touches Method") {
    mylibrary::Location origin_(0,0);
    REQUIRE(origin_.Touches(mylibrary::Location(1,0)));
    REQUIRE(origin_.Touches(mylibrary::Location(-1,0)));
    REQUIRE(origin_.Touches(mylibrary::Location(0,1)));
    REQUIRE(origin_.Touches(mylibrary::Location(0,-1)));

    mylibrary::Segment test_segment_ (origin_, mylibrary::blue);
    REQUIRE(test_segment_.Touches(mylibrary::Segment(mylibrary::Location(1,0), mylibrary::green)));
    REQUIRE(test_segment_.Touches(mylibrary::Segment(mylibrary::Location(-1,0), mylibrary::red)));
    REQUIRE(test_segment_.Touches(mylibrary::Segment(mylibrary::Location(0,1), mylibrary::blue)));
    REQUIRE(test_segment_.Touches(mylibrary::Segment(mylibrary::Location(0,-1), mylibrary::red)));

    REQUIRE(!test_segment_.Touches(mylibrary::Segment(mylibrary::Location(2,0), mylibrary::green)));
    REQUIRE(!test_segment_.Touches(mylibrary::Segment(mylibrary::Location(-1,-9), mylibrary::red)));
    REQUIRE(!test_segment_.Touches(mylibrary::Segment(mylibrary::Location(10,1), mylibrary::blue)));
    REQUIRE(!test_segment_.Touches(mylibrary::Segment(mylibrary::Location(8,-1), mylibrary::red)));
}