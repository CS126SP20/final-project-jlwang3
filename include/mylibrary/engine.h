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
#include <vector>
#include <random>
#include "piece.h"
#include "segment.h"

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
         * Executes a time step: moves the current piece, spawns in new pieces, and prevents collisions.
         */
        void Step();
        /**
         * Checks if the current piece is touching bottom, if so, spawn in a new piece.
         */
        bool IsTouchingBottom();
        /**
         * Start the Game Over.
         */
        void Reset();
        /**
         * Spawn a new piece.
         */
        void NewPiece();
        /**
         * Changes the direction of the piece for the next time step.
         */
        void SetDirection(Direction);

        std::vector<Segment> GetCurrentPiece() const;

        std::vector<Segment> GetAllPieces() const;

    private:
        /**
         * Generate random location on the top row where row = 0
         * DISCLAIMER: Need to check for overlapping tiles before spawning new piece
         */
        Location GetRandomLocation();
        Color GetRandomColor();
        Piece GetRandomPieceType();
        /**
         * Very Important!
         * Keeps track of GameOver(), piece collisions, removing a full row.
         */
        std::vector<Location> GetCurrentOccupiedTiles();
        /**
         * Removes a full row.
         */
        void RemoveRow(int);
        bool GameOver();
        int RandomInt(int, int);

    private:
        const size_t width_;
        const size_t height_;
        std::vector<Segment> * current_piece_;
        std::vector<Segment> all_pieces_;
        Direction direction_;
        std::random_device rd_;
    };
}
#endif //FINALPROJECT_ENGINE_H
