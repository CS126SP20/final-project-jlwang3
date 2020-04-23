//
// Created by Jeffrey Wang on 4/22/20.
//

#include <mylibrary/piece.h>

#include <utility>

namespace mylibrary {

    Piece::Piece(std::vector<Segment> piece) : piece_(std::move(piece)) {}

    void Piece::MoveRight() {
        for (int i = 0; i < piece_.size(); ++i) {
            piece_[i].SetLocation(piece_[i].GetLocation() + mylibrary::Location(1,0));
        }
    }

    void Piece::MoveLeft() {
        for (int i = 0; i < piece_.size(); ++i) {
            piece_[i].SetLocation(piece_[i].GetLocation() - mylibrary::Location(1,0));
        }
    }

    void Piece::MoveUp() {
        for (int i = 0; i < piece_.size(); ++i) {
            piece_[i].SetLocation(piece_[i].GetLocation() + mylibrary::Location(0,1));
        }
    }

    void Piece::MoveDown() {
        for (int i = 0; i < piece_.size(); ++i) {
            piece_[i].SetLocation(piece_[i].GetLocation() - mylibrary::Location(0,1));
        }
    }
}