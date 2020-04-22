// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>


namespace myapp {

using cinder::app::KeyEvent;

const char kDbPath[] = "final_project.db";

MyApp::MyApp()
    :leaderboard_{cinder::app::getAssetPath(kDbPath).string()}
    {}

void MyApp::setup() {
    mylibrary::Player test_player{"Jeffrey", 10101};
    leaderboard_.AddScoreToLeaderBoard(test_player);
}

void MyApp::update() { }

void MyApp::draw() { }

void MyApp::keyDown(KeyEvent event) { }

}  // namespace myapp
