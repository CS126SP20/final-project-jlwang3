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

    std::vector<Segment> Engine::GetPiece() const {
        return std::vector<Segment> {
            Segment(Location(0,0), mylibrary::yellow),
            Segment(Location(1,0), mylibrary::yellow),
            Segment(Location(2,0), mylibrary::yellow),
            Segment(Location(1,1), mylibrary::yellow)
        };
    }
}