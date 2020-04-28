//
// Created by Jeffrey Wang on 4/22/20.
//

#include <mylibrary/piece.h>

#include <utility>

namespace mylibrary {

    Piece::Piece() : piece_{}  {

    }

    size_t Piece::Size() const {
        return piece_.size();
    }

    std::vector<Segment>::iterator Piece::begin() {
        piece_.begin();
    }

    std::vector<Segment>::iterator Piece::end() {
        piece_.end();
    }

    std::vector<Segment>::const_iterator Piece::cbegin() {
        piece_.cbegin();
    }

    std::vector<Segment>::const_iterator Piece::cend() {
        piece_.cend();
    }

    Piece::Piece(std::vector<Segment> piece) {
        piece_ = std::move(piece);
    }

    Segment Piece::Front() const {
        return piece_.front();
    }

    Segment Piece::Back() const {
        return piece_.back();
    }
}