//
// Created by Jeffrey Wang on 4/22/20.
//

#include <mylibrary/engine.h>

namespace mylibrary {
Engine::Engine() {

}

void Engine::Step() {

}

    void Engine::SetDirection(Direction direction) {
        direction_ = direction;
        switch (direction_) {
            case Direction::kUp:
                piece_.MoveUp()
            case Direction::kDown:
                piece_.MoveDown();
            case Direction::kLeft:
                piece_
            case Direction::kRight:
                return {0, +1};
        }
    }
}