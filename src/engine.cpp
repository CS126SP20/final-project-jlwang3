//
// Created by Jeffrey Wang on 4/22/20.
//

#include <mylibrary/engine.h>
#include <mylibrary//pieces.h>
#include <vector>
#include <utility>

namespace mylibrary {

    Piece Engine::GetPiece() const {
        return piece_;
    }

    void Engine::Reset() {
        piece_ = {};
        Location location = GetRandomLocation();
        Color color = GetRandomColor();
        PieceType piece_type = GetRandomPieceType();
        if (piece_type == mylibrary::I) {
            piece_ = Piece(std::vector<Segment>{Segment(location + mylibrary::Location(0,0), color),
            Segment(location + mylibrary::Location(0,1), color),
            Segment(location + mylibrary::Location(0,2), color),
            Segment(location + mylibrary::Location(0,3), color)});
        } else if (piece_type == mylibrary::O) {
            piece_ = Piece(std::vector<Segment>{
                    Segment(location + mylibrary::Location(0,0), color),
                    Segment(location + mylibrary::Location(1, 0), color),
                    Segment(location + mylibrary::Location(0, 1), color),
                    Segment(location + mylibrary::Location(1, 1), color)
            });
        } else if (piece_type == mylibrary::T) {
            piece_ = Piece(std::vector<Segment>{
                    Segment(location + mylibrary::Location(0,0), color),
                    Segment(location + mylibrary::Location(1, 0), color),
                    Segment(location + mylibrary::Location(2, 0), color),
                    Segment(location + mylibrary::Location(1, 1), color)
            });
        } else if (piece_type == mylibrary::S) {
            piece_ = Piece(std::vector<Segment>{
                    Segment(location + mylibrary::Location(0, 0), color),
                    Segment(location + mylibrary::Location(1, 0), color),
                    Segment(location + mylibrary::Location(1, 1), color),
                    Segment(location + mylibrary::Location(2, 1), color)
            });
        } else if (piece_type == mylibrary::Z) {
            piece_ = Piece(std::vector<Segment>{
                    Segment(location + mylibrary::Location(0, 1), color),
                    Segment(location + mylibrary::Location(1, 1), color),
                    Segment(location + mylibrary::Location(1, 0), color),
                    Segment(location + mylibrary::Location(2, 0), color)
            });
        } else if (piece_type == mylibrary::J) {
            piece_ = Piece(std::vector<Segment>{
                    Segment(location + mylibrary::Location(0, 0), color),
                    Segment(location + mylibrary::Location(1, 0), color),
                    Segment(location + mylibrary::Location(1, 1), color),
                    Segment(location + mylibrary::Location(1, 2), color)
            });
        } else {
            piece_ = Piece(std::vector<Segment>{
                Segment(location + mylibrary::Location(0, 2), color),
                Segment(location + mylibrary::Location(0, 1), color),
                Segment(location + mylibrary::Location(0, 0), color),
                Segment(location + mylibrary::Location(1, 0), color)
        });
        }
    }

    Engine::Engine(size_t width, size_t height) : width_{width},
                                                  height_{height},
                                                  direction_{Direction::kDown}
                                                  {Reset();}

    /**
     * Converts a direction into a delta location.
     */
    Location FromDirection(const Direction direction) {
        switch (direction) {
            case Direction::kUp:
                return {-1, 0};
            case Direction::kDown:
                return {+1, 0};
            case Direction::kLeft:
                return {0, -1};
            case Direction::kRight:
                return {0, +1};
        }
    }

    void Engine::Step() {
        Location d_loc = FromDirection(direction_);
        const std::vector<Location> old_occupied_tiles = GetOccupiedTiles();
        Location leader = (piece_.Front().GetLocation() + d_loc) % Location(height_,width_);
        for (Segment& block : piece_) {
            Location old = block.GetLocation();
            block.SetLocation(leader);
            leader = old;
        }
    }

    std::vector<Location> Engine::GetOccupiedTiles() {
        std::vector<Location> occupied_tiles;

        for (const Segment& part : piece_) {
            occupied_tiles.push_back(part.GetLocation());
        }

        return occupied_tiles;
    }

    Location Engine::GetRandomLocation() {
        std::vector<Location> occupied_tiles = GetOccupiedTiles();

        Location final_location(0, 0);

        for (size_t row = 0; row < height_; ++row) {
            for (size_t col = 0; col < width_; ++col) {
                Location loc(row, col);
                for (int i = 0; i < occupied_tiles.size(); ++i) {
                    if (occupied_tiles[i] == loc) break;
                }
                final_location = loc;
            }
        }

        return final_location;
    }

    Color Engine::GetRandomColor() {
        return static_cast<Color> (rand() % yellow);
    }

    PieceType Engine::GetRandomPieceType() {
        return static_cast<PieceType> (rand() % L);
    }

    void Engine::SetDirection(Direction direction) {
        direction_ = direction;
    }
}