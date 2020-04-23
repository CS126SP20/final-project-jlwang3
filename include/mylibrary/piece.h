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
        explicit Piece(std::vector<Segment> piece);
        /**
         * Moves the piece right.
         */
        void MoveRight();
        /**
         * Moves the piece left.
         */
        void MoveLeft();
        /**
         * Moves the piece up.
         */
         void MoveUp();
        /**
         * Moves the piece down.
         */
        void MoveDown();
        /**
         * Same Segments
         */
    private:
        size_t board_size_ = 10;
        /**
         * Represents a piece
         */
        std::vector<Segment> piece_;
    };
}
#endif //FINALPROJECT_PIECE_H
