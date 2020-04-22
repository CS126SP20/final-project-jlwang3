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
        void MoveRight();
        void MoveLeft();
        void DropDown();
    private:
        std::vector<Segment> piece_;
    };
}
#endif //FINALPROJECT_PIECE_H
