// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <mylibrary/leaderboard.h>
#include <mylibrary/engine.h>
#include <mylibrary/direction.h>

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"

using namespace ci;
using namespace ci::app;
using namespace std;

namespace myapp {

    enum class GameState {
        kPlaying
    };

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  void keyUp(cinder::app::KeyEvent) override;

private:
  void DrawPiece() const;
  void ResetGame();

private:
    mylibrary::Engine engine_;
    mylibrary::LeaderBoard leaderboard_;
    const std::string player_name_;
    std::vector<mylibrary::Player> top_players_;
    std::chrono::time_point<std::chrono::system_clock> last_time_;
    const size_t speed_;
    GameState state_;
    const size_t tile_size_;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
