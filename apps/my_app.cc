// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <mylibrary/segment.h>
#include <gflags/gflags.h>
#include <cinder/Font.h>
#include <cinder/Text.h>

namespace myapp {

    const double kRate = 25;
    const size_t kLimit = 3;
    using cinder::Color;
    using cinder::ColorA;
    using cinder::Rectf;
    using cinder::app::KeyEvent;
    using cinder::gl::Texture2d;

    const char kDbPath[] = "final_project.db";

    const char kNormalFont[] = "Arial";
    const char kBoldFont[] = "Arial Bold";
    const char kDifferentFont[] = "Papyrus";

    DECLARE_uint32(difficulty);
    DECLARE_uint32(width);
    DECLARE_uint32(height);
    DECLARE_uint32(tilesize);
    DECLARE_uint32(speed);
    DECLARE_string(name);

    MyApp::MyApp()
    : leaderboard_{cinder::app::getAssetPath(kDbPath).string()},
      player_name_{FLAGS_name},
      state_{GameState::kPlaying},
      engine_(FLAGS_width,FLAGS_height, FLAGS_difficulty),
      tile_size_{FLAGS_tilesize},
      speed_{FLAGS_speed} {}

void MyApp::setup() {
    cinder::gl::enableDepthWrite();
    cinder::gl::enableDepthRead();
    }

void MyApp::update() {
    if (engine_.GameOver()) {
        state_ = GameState::kGameOver;
    }
    if (state_ == GameState::kGameOver) {
        if (top_players_.empty()) {
            leaderboard_.AddScoreToLeaderBoard({player_name_, engine_.GetScore()});
            top_players_ = leaderboard_.RetrieveHighScores(kLimit);

            // It is crucial the this vector be populated, given that `kLimit` > 0.
            assert(!top_players_.empty());
        }
        return;
    }

    const auto time = std::chrono::system_clock::now();
    if (time - last_time_ > std::chrono::milliseconds(speed_)) {
        engine_.Step();
        last_time_ = time;
    }
    std::cout << engine_.GetCurrentPiece().front().GetLocation() << std::endl;
}

void MyApp::draw() {
    if (state_ == GameState::kGameOver) {
        if (!printed_game_over_) cinder::gl::clear(Color(1, 0, 0));
        DrawGameOver();
        return;
    }
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
            engine_.SetRotation(mylibrary::Rotation::kClockwise);
            break;
        }
        case KeyEvent::KEY_UP:{
            engine_.SetRotation(mylibrary::Rotation::kCounterclockwise);
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
        case KeyEvent::KEY_r: {
            ResetGame();
            break;
        }
    }
}

    void MyApp::keyUp(KeyEvent event) {
        switch (event.getCode()) {
            case KeyEvent::KEY_DOWN:{
                engine_.SetRotation(mylibrary::Rotation::kStill);
                break;
            }
            case KeyEvent::KEY_UP:{
                engine_.SetRotation(mylibrary::Rotation::kStill);
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
        printed_game_over_ = false;
        state_ = GameState::kPlaying;
        top_players_.clear();
    }

    template <typename C>
    void PrintText(const string& text, const C& color, const cinder::ivec2& size,
                   const cinder::vec2& loc) {
        cinder::gl::color(color);

        auto box = TextBox()
                .alignment(TextBox::CENTER)
                .font(cinder::Font(kNormalFont, 30))
                .size(size)
                .color(color)
                .backgroundColor(ColorA(0, 0, 0, 0))
                .text(text);

        const auto box_size = box.getSize();
        const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
        const auto surface = box.render();
        const auto texture = cinder::gl::Texture::create(surface);
        cinder::gl::draw(texture, locp);
    }

    void MyApp::DrawGameOver() {
        if (printed_game_over_) return;
        if (top_players_.empty()) return;

        const cinder::vec2 center = getWindowCenter();
        const cinder::ivec2 size = {500, 50};
        const Color color = Color::black();

        size_t row = 0;
        PrintText("Game Over :(", color, size, center);
        for (const mylibrary::Player& player : top_players_) {
            std::stringstream ss;
            ss << player.name << " - " << player.score;
            PrintText(ss.str(), color, size, {center.x, center.y + (++row) * 50});
        }

        printed_game_over_ = true;
    }
}  // namespace myapp
