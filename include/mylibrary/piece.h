//
// Created by Jeffrey Wang on 4/22/20.
//

#ifndef FINALPROJECT_PIECE_H
#define FINALPROJECT_PIECE_H

#include <vector>
#include <mylibrary/segment.h>

namespace mylibrary {
    class Piece {
    public:
        Piece();
        explicit Piece(std::vector<Segment>);
        /**
         * Returns the size of the piece.
         */
        size_t Size() const;

        Segment Front() const;
        Segment Back() const;

        std::vector<Segment>::iterator begin();

        std::vector<Segment>::iterator end();

        std::vector<Segment>::const_iterator cbegin();

        std::vector<Segment>::const_iterator cend();

    private:
        /**
         * Represents a piece
         */
        std::vector<Segment> piece_;
    };
}
#endif //FINALPROJECT_PIECE_H
