//
// Created by Jeffrey Wang on 4/22/20.
//

#include <mylibrary/piece.h>

#include <utility>

namespace mylibrary {

    Piece::Piece(std::vector<Segment> piece) : piece_(std::move(piece)) {}

    void Piece::MoveRight() {
        for (int i = 0; i < piece_.size(); ++i) {
            piece_[i].SetLocation((piece_[i].GetLocation() + mylibrary::Location(1,0)) % Location(board_size_, board_size_));
        }
    }

    void Piece::MoveLeft() {
        for (int i = 0; i < piece_.size(); ++i) {
            piece_[i].SetLocation((piece_[i].GetLocation() - mylibrary::Location(1,0)) % Location(board_size_, board_size_));
        }
    }

    void Piece::MoveUp() {
        for (int i = 0; i < piece_.size(); ++i) {
            piece_[i].SetLocation((piece_[i].GetLocation() + mylibrary::Location(0,1)) % Location(board_size_,board_size_));
        }
    }

    void Piece::MoveDown() {
        for (int i = 0; i < piece_.size(); ++i) {
            piece_[i].SetLocation((piece_[i].GetLocation() - mylibrary::Location(0,1)) % Location(board_size_,board_size_));
        }
    }

    std::vector<Segment>::iterator Piece::begin() {
        return std::vector<Segment, std::allocator<Segment>>::iterator();
    }

    std::vector<Segment>::iterator Piece::end() {
        return std::vector<Segment, std::allocator<Segment>>::iterator();
    }

    std::vector<Segment>::const_iterator Piece::cbegin() {
        return std::vector<Segment, std::allocator<Segment>>::const_iterator();
    }

    std::vector<Segment>::const_iterator Piece::cend() {
        return std::vector<Segment, std::allocator<Segment>>::const_iterator();
    }
}