//
// Created by Jeffrey Wang on 4/22/20.
//

#ifndef FINALPROJECT_ENGINE_H
#define FINALPROJECT_ENGINE_H

#include <cstdio>
#include <mylibrary/direction.h>
#include <mylibrary/location.h>
#include <mylibrary/piece.h>
#include <set>
#include "pieces.h"

namespace mylibrary {
    /**
     * The engine enables us to interact with the game.
     */
    class Engine {
    public:
        /**
         * Create a 10x10 game board.
         */
        Engine();
        /**
         * Sets the direction for the Step() Method.
         */
        void SetDirection(Direction);
        /**
         * Moves the piece in any direction
         */
        void Step();
        /**
         * Start game over.
         */
        void Reset();

        Piece GetPiece(mylibrary::Pieces pieces) const;

    private:
        std::set<Location> GetOccupiedTiles();

    private:
        size_t board_size_ = 10;
        Direction direction_;
        Piece piece_;
    };
}
#endif //FINALPROJECT_ENGINE_H
