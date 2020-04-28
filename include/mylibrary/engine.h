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
         * Creates a new snake game of the given size.
         */
        Engine(size_t width, size_t height);
        /**
         * Executes a time step: moves the piece.
         */
        void Step();
        /**
         * Start the game over.
         */
        void Reset();
        /**
         * Changes the direction of the piece for the next time step.
         */
        void SetDirection(Direction);
        size_t GetScore() const;
        Piece GetPiece() const;

    //private:
        Location GetRandomLocation();
        Color GetRandomColor();
        PieceType GetRandomPieceType();
        std::vector<Location> GetOccupiedTiles();

    private:
        const size_t width_;
        const size_t height_;
        Piece piece_;
        Direction direction_;
    };
}
#endif //FINALPROJECT_ENGINE_H
