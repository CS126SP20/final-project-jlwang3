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
        /**
         * Moves the piece right.
         */
        void MoveRight();
        /**
         * Moves the piece left.
         */
        void MoveLeft();
        /**
         * Drops the piece down.
         */
        void DropDown();
    private:
        /**
         * Represents a piece
         */
        std::vector<Segment> piece_;
    };
}
#endif //FINALPROJECT_PIECE_H
