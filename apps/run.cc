// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <cinder/app/App.h>
#include <cinder/app/RendererGl.h>

#include "my_app.h"
#include <gflags/gflags.h>>

using cinder::app::App;
using cinder::app::RendererGl;


namespace myapp {

    DEFINE_uint32(width, 10, "the number of tiles in each row");
    DEFINE_uint32(height,20,"the number of tiles in each column");
    DEFINE_uint32(tilesize, 40, "the size of each tile");
    DEFINE_uint32(speed, 200, "the speed (delay) of the game");
    DEFINE_string(name, "CS126SP20", "the name of the player");

const int kSamples = 8;

    void ParseArgs(vector<string>* args) {
        gflags::SetUsageMessage(
                "Play a game of Snake. Pass --helpshort for options.");
        int argc = static_cast<int>(args->size());

        vector<char*> argvs;
        for (string& str : *args) {
            argvs.push_back(&str[0]);
        }

        char** argv = argvs.data();
        gflags::ParseCommandLineFlags(&argc, &argv, true);
    }

void SetUp(App::Settings* settings) {
    vector<string> args = settings->getCommandLineArgs();
    ParseArgs(&args);

    const int width = static_cast<int>(FLAGS_width * FLAGS_tilesize);
    const int height = static_cast<int>(FLAGS_height * FLAGS_tilesize);
    settings->setWindowSize(width, height);
    settings->setResizable(false);
    settings->setTitle("CS 126 Snake");
}

}  // namespace myapp


// This is a macro that runs the application.
CINDER_APP(myapp::MyApp,
           RendererGl(RendererGl::Options().msaa(myapp::kSamples)),
           myapp::SetUp)
