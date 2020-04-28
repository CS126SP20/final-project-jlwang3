// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <mylibrary/segment.h>

const double kRate = 25;

namespace myapp {
    using cinder::ColorA;
    using cinder::Rectf;
using cinder::app::KeyEvent;

const char kDbPath[] = "final_project.db";

MyApp::MyApp()
    : leaderboard_{cinder::app::getAssetPath(kDbPath).string()},
      state_{GameState::kPlaying}, engine_(mylibrary::Piece(std::vector<mylibrary::Segment>{
                mylibrary::Segment(mylibrary::Location(0, 2), mylibrary::yellow),
                mylibrary::Segment(mylibrary::Location(0, 1), mylibrary::yellow),
                mylibrary::Segment(mylibrary::Location(0, 0), mylibrary::yellow),
                mylibrary::Segment(mylibrary::Location(1, 0), mylibrary::yellow)
        })) {}

void MyApp::setup() {cinder::gl::enableDepthWrite();
    cinder::gl::enableDepthRead();}

void MyApp::update() {
    engine_.Step();
}

void MyApp::draw() {
    DrawPiece();
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

    void MyApp::DrawPiece() const {
        int num_visible = 0;
        for (const mylibrary::Segment& part : engine_.GetPiece(mylibrary::L)) {
            const mylibrary::Location loc = part.GetLocation();
            const double opacity = std::exp(-(num_visible++) / kRate);
            cinder::gl::color(ColorA(0, 0, 1, static_cast<float>(opacity)));
            cinder::gl::drawSolidRect(Rectf(tile_size_ * loc.Row(),
                                            tile_size_ * loc.Col(),
                                            tile_size_ * loc.Row() + tile_size_,
                                            tile_size_ * loc.Col() + tile_size_));
        }
        const cinder::vec2 center = getWindowCenter();
    }

}  // namespace myapp
