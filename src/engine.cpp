//
// Created by Jeffrey Wang on 4/22/20.
//

#include <mylibrary/engine.h>
#include <mylibrary//pieces.h>

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

    Piece Engine::GetPiece(Pieces pieces) const {
        if (pieces == mylibrary::I) {
            return Piece(std::vector<Segment>{
                    Segment(mylibrary::Location(0, 0), mylibrary::yellow),
                    Segment(mylibrary::Location(1, 0), mylibrary::yellow),
                    Segment(mylibrary::Location(2, 0), mylibrary::yellow),
                    Segment(mylibrary::Location(3, 0), mylibrary::yellow)
            });
        }
        if (pieces == mylibrary::O) {
            return Piece(std::vector<Segment>{
                    Segment(mylibrary::Location(0, 0), mylibrary::yellow),
                    Segment(mylibrary::Location(1, 0), mylibrary::yellow),
                    Segment(mylibrary::Location(0, 1), mylibrary::yellow),
                    Segment(mylibrary::Location(1, 1), mylibrary::yellow)
            });
        }
        if (pieces == mylibrary::T) {
            return Piece(std::vector<Segment>{
                    Segment(mylibrary::Location(0, 0), mylibrary::yellow),
                    Segment(mylibrary::Location(1, 0), mylibrary::yellow),
                    Segment(mylibrary::Location(2, 0), mylibrary::yellow),
                    Segment(mylibrary::Location(1, 1), mylibrary::yellow)
            });
        }
        if (pieces == mylibrary::S) {
            return Piece(std::vector<Segment>{
                    Segment(mylibrary::Location(0, 0), mylibrary::yellow),
                    Segment(mylibrary::Location(1, 0), mylibrary::yellow),
                    Segment(mylibrary::Location(1, 1), mylibrary::yellow),
                    Segment(mylibrary::Location(2, 1), mylibrary::yellow)
            });
        }
        if (pieces == mylibrary::Z) {
            return Piece(std::vector<Segment>{
                    Segment(mylibrary::Location(0, 1), mylibrary::yellow),
                    Segment(mylibrary::Location(1, 1), mylibrary::yellow),
                    Segment(mylibrary::Location(1, 0), mylibrary::yellow),
                    Segment(mylibrary::Location(2, 0), mylibrary::yellow)
            });
        }
        if (pieces == mylibrary::J) {
            return Piece(std::vector<Segment>{
                    Segment(mylibrary::Location(0, 0), mylibrary::yellow),
                    Segment(mylibrary::Location(1, 0), mylibrary::yellow),
                    Segment(mylibrary::Location(1, 1), mylibrary::yellow),
                    Segment(mylibrary::Location(1, 2), mylibrary::yellow)
            });
        }
        return Piece(std::vector<Segment>{
                Segment(mylibrary::Location(0, 2), mylibrary::yellow),
                Segment(mylibrary::Location(0, 1), mylibrary::yellow),
                Segment(mylibrary::Location(0, 0), mylibrary::yellow),
                Segment(mylibrary::Location(1, 0), mylibrary::yellow)
        });
    }
}