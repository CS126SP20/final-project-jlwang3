// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <mylibrary/segment.h>

namespace myapp {

    const double kRate = 25;
    using cinder::ColorA;
    using cinder::Rectf;
    using cinder::app::KeyEvent;
    using cinder::gl::Texture2d;

    const char kDbPath[] = "final_project.db";

    MyApp::MyApp()
    : leaderboard_{cinder::app::getAssetPath(kDbPath).string()},
      state_{GameState::kPlaying}, engine_(10,10),
      tile_size_{80},
      speed_{50} {}

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
}

void MyApp::draw() {
    cinder::gl::enableAlphaBlending();

    cinder::gl::clear();
    DrawPiece();
}

    void MyApp::DrawPiece() const {
        int num_visible = 0;
        for (const mylibrary::Segment& part : engine_.GetPiece()) {
            const mylibrary::Location loc = part.GetLocation();
            cinder::gl::color(ColorA(0, 0, 1));
            cinder::gl::drawSolidRect(Rectf(tile_size_ * loc.Row(),
                                            tile_size_ * loc.Col(),
                                            tile_size_ * loc.Row() + tile_size_,
                                            tile_size_ * loc.Col() + tile_size_));
        }
        const cinder::vec2 center = getWindowCenter();
    }

void MyApp::keyDown(KeyEvent event) {
    switch (event.getCode()) {
        case KeyEvent::KEY_UP:
        case KeyEvent::KEY_k:
        case KeyEvent::KEY_w: {
            engine_.SetDirection(mylibrary::Direction::kUp);
            break;
        }
        case KeyEvent::KEY_DOWN:
        case KeyEvent::KEY_j:
        case KeyEvent::KEY_s: {
            engine_.SetDirection(mylibrary::Direction::kDown);
            break;
        }
        case KeyEvent::KEY_LEFT:
        case KeyEvent::KEY_h:
        case KeyEvent::KEY_a: {
            engine_.SetDirection(mylibrary::Direction::kLeft);
            break;
        }
        case KeyEvent::KEY_RIGHT:
        case KeyEvent::KEY_l:
        case KeyEvent::KEY_d: {
            engine_.SetDirection(mylibrary::Direction::kRight);
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
