// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <mylibrary/leaderboard.h>
#include <mylibrary/engine.h>
#include <mylibrary/direction.h>

namespace myapp {

    enum class GameState {
        kPlaying,
        kCountDown,
        kGameOver,
    };

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;

private:
  void DrawPiece() const;

private:
    mylibrary::Engine engine_;
    mylibrary::LeaderBoard leaderboard_;
    const std::string player_name_;
    std::vector<mylibrary::Player> top_players_;
    GameState state_;
    const size_t tile_size_ = 80;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
