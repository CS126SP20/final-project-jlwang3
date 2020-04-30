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
#include "rotation.h"

namespace mylibrary {
    /**
     * The engine enables us to interact with the game.
     */
    class Engine {
    public:
        /**
         * Creates a new snake game of the given size.
         */
        Engine(size_t width, size_t height, int difficulty);
        /**
         * Executes a time step: moves the current piece, spawns in new pieces, and prevents collisions.
         */
        void Step();
        /**
         * Checks if the current piece is touching bottom, if so, spawn in a new piece.
         */
        bool IsTouchingBottom();
        /**
         * Checks if there are sufficient touches between same color pieces.
         * Removes them if so,
         * and drops remaining pieces.
         */
        void UpdateAllPieces();
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

        /**
         * Changes the rotation of the piece for the next time step.
         */
        void SetRotation(Rotation);

        std::vector<Segment> GetCurrentPiece() const;

        std::vector<Segment> GetAllPieces() const;

    private:
        /**
         * Each pair of touching segments counts as a touch.
         */
        static int NumberOfTouches(std::vector<Segment>);
        /**
         * Removes the given segments from the all_pieces_ vector.
         */
        void RemoveSegments(Color color);
        /**
         * This method drops all the remaining pieces.
         */
        void DropAllPieces();
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
         bool GameOver();
         size_t GetScore();
         int RandomInt(int, int);


    private:
        const size_t width_;
        const size_t height_;
        std::vector<Segment> * current_piece_;
        std::vector<Segment> all_pieces;
        Direction direction_;
        Rotation rotation_;
        std::random_device rd_;
        size_t score_;
        int difficulty_;
    };
}
#endif //FINALPROJECT_ENGINE_H
