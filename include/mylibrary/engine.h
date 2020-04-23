//
// Created by Jeffrey Wang on 4/22/20.
//

#ifndef FINALPROJECT_ENGINE_H
#define FINALPROJECT_ENGINE_H

#include <cstdio>
#include <mylibrary/direction.h>
#include <mylibrary/location.h>
#include <mylibrary/piece.h>

namespace mylibrary {
    /**
     * The engine should enforce the fact that pieces do not overlap and do not go outside the boundary.
     */
     class Engine {
     public:
         void SetDirection(Direction);
         void Step();

     private:
         size_t board_size_ = 10;
         Direction direction_;
         Piece piece_;
     };
}
#endif //FINALPROJECT_ENGINE_H
