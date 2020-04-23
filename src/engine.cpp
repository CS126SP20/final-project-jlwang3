//
// Created by Jeffrey Wang on 4/22/20.
//

#include <mylibrary/engine.h>

namespace mylibrary {
void Engine::Step() {
    switch (direction_) {
        case Direction::kUp:
            piece_.MoveUp();
        case Direction::kDown:
            piece_.MoveDown();
        case Direction::kLeft:
            piece_.MoveLeft();
        case Direction::kRight:
            piece_.MoveRight();
    }
}

    void Engine::SetDirection(Direction direction) {
        direction_ = direction;
    }
}