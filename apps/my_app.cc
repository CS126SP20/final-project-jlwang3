// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <mylibrary/segment.h>
#include <gflags/gflags.h>

namespace myapp {

    const double kRate = 25;
    using cinder::ColorA;
    using cinder::Rectf;
    using cinder::app::KeyEvent;
    using cinder::gl::Texture2d;

    const char kDbPath[] = "final_project.db";

    DECLARE_uint32(width);
    DECLARE_uint32(height);
    DECLARE_uint32(tilesize);
    DECLARE_uint32(speed);
    DECLARE_string(name);

    MyApp::MyApp()
    : leaderboard_{cinder::app::getAssetPath(kDbPath).string()},
      state_{GameState::kPlaying},
      engine_(FLAGS_width,FLAGS_height),
      tile_size_{FLAGS_tilesize},
      speed_{FLAGS_speed},
      player_name_{FLAGS_name}{}

void MyApp::setup() {
    cinder::gl::enableDepthWrite();
    cinder::gl::enableDepthRead();
    }

void MyApp::update() {
    const auto time = std::chrono::system_clock::now();
    if (time - last_time_ > std::chrono::milliseconds(speed_)) {
        engine_.Step();
        last_time_ = time;
    }
    std::cout << engine_.GetCurrentPiece().front().GetLocation() << std::endl;
}

void MyApp::draw() {
    cinder::gl::enableAlphaBlending();
    cinder::gl::clear();
    DrawPieces();
}

    void MyApp::DrawPieces() const {
        for (int i = 0; i < engine_.GetAllPieces().size(); ++i) {
            const mylibrary::Location loc = engine_.GetAllPieces()[i].GetLocation();
            if (engine_.GetAllPieces()[i].GetColor() == mylibrary::red) cinder::gl::color(ColorA(1,0,0));
            if (engine_.GetAllPieces()[i].GetColor() == mylibrary::green) cinder::gl::color(ColorA(0,1,0));
            if (engine_.GetAllPieces()[i].GetColor() == mylibrary::blue) cinder::gl::color(ColorA(0,0,1));
            cinder::gl::drawSolidRect(Rectf(tile_size_ * loc.Row(),
                    tile_size_ * loc.Col(),
                    tile_size_ * loc.Row() + tile_size_,
                    tile_size_ * loc.Col() + tile_size_));
        }
        for (int i = 0; i < engine_.GetCurrentPiece().size(); ++i) {
            const mylibrary::Location loc = engine_.GetCurrentPiece()[i].GetLocation();
            if (engine_.GetCurrentPiece()[i].GetColor() == mylibrary::red) cinder::gl::color(ColorA(1,0,0));
            if (engine_.GetCurrentPiece()[i].GetColor() == mylibrary::green) cinder::gl::color(ColorA(0,1,0));
            if (engine_.GetCurrentPiece()[i].GetColor() == mylibrary::blue) cinder::gl::color(ColorA(0,0,1));
            cinder::gl::drawSolidRect(Rectf(tile_size_ * loc.Row(),
                                            tile_size_ * loc.Col(),
                                            tile_size_ * loc.Row() + tile_size_,
                                            tile_size_ * loc.Col() + tile_size_));
        }
        const cinder::vec2 center = getWindowCenter();
    }

void MyApp::keyDown(KeyEvent event) {
    switch (event.getCode()) {
        case KeyEvent::KEY_DOWN:{
            engine_.SetDirection(mylibrary::Direction::kDown);
            break;
        }
        case KeyEvent::KEY_LEFT: {
            engine_.SetDirection(mylibrary::Direction::kLeft);
            break;
        }
        case KeyEvent::KEY_RIGHT: {
            engine_.SetDirection(mylibrary::Direction::kRight);
            break;
        }
    }
}

    void MyApp::keyUp(KeyEvent event) {
        switch (event.getCode()) {
            case KeyEvent::KEY_DOWN:{
                engine_.SetDirection(mylibrary::Direction::kDown);
                break;
            }
            case KeyEvent::KEY_LEFT: {
                engine_.SetDirection(mylibrary::Direction::kDown);
                break;
            }
            case KeyEvent::KEY_RIGHT: {
                engine_.SetDirection(mylibrary::Direction::kDown);
                break;
            }
        }
    }

    void MyApp::ResetGame() {
        engine_.Reset();
        state_ = GameState::kPlaying;
        top_players_.clear();
    }
}  // namespace myapp
