//
// Created by Jeffrey Wang on 4/22/20.
//

#include <mylibrary/engine.h>
#include <mylibrary/piece.h>
#include <vector>
#include <utility>

namespace mylibrary {

    std::vector<Segment> Engine::GetPiece() const {
        return piece_;
    }

    void Engine::Reset() {
        piece_ = {};
        Location location = GetRandomLocation();
        Color color = GetRandomColor();
        Piece piece_type = GetRandomPieceType();
        if (piece_type == mylibrary::I) {
            piece_ = std::vector<Segment>{Segment((location + mylibrary::Location(0,0)) % Location(height_,width_), color),
            Segment((location + mylibrary::Location(0,1)) % Location(height_,width_), color),
            Segment((location + mylibrary::Location(0,2)) % Location(height_,width_), color),
            Segment((location + mylibrary::Location(0,3)) % Location(height_,width_), color)};
        } else if (piece_type == mylibrary::O) {
            piece_ = std::vector<Segment>{
                    Segment((location + mylibrary::Location(0,0)) % Location(height_,width_), color),
                    Segment((location + mylibrary::Location(1, 0)) % Location(height_,width_), color),
                    Segment((location + mylibrary::Location(0, 1)) % Location(height_,width_), color),
                    Segment((location + mylibrary::Location(1, 1)) % Location(height_,width_), color)
            };
        } else if (piece_type == mylibrary::T) {
            piece_ = std::vector<Segment>{
                    Segment((location + mylibrary::Location(0,0)) % Location(height_,width_), color),
                    Segment((location + mylibrary::Location(1, 0)) % Location(height_,width_), color),
                    Segment((location + mylibrary::Location(2, 0)) % Location(height_,width_), color),
                    Segment((location + mylibrary::Location(1, 1)) % Location(height_,width_), color)
            };
        } else if (piece_type == mylibrary::S) {
            piece_ = std::vector<Segment>{
                    Segment((location + mylibrary::Location(0, 0)) % Location(height_,width_), color),
                    Segment((location + mylibrary::Location(1, 0)) % Location(height_,width_), color),
                    Segment((location + mylibrary::Location(1, 1)) % Location(height_,width_), color),
                    Segment((location + mylibrary::Location(2, 1)) % Location(height_,width_), color)
            };
        } else if (piece_type == mylibrary::Z) {
            piece_ = std::vector<Segment>{
                    Segment((location + mylibrary::Location(0, 1)) % Location(height_,width_), color),
                    Segment((location + mylibrary::Location(1, 1)) % Location(height_,width_), color),
                    Segment((location + mylibrary::Location(1, 0)) % Location(height_,width_), color),
                    Segment((location + mylibrary::Location(2, 0)) % Location(height_,width_), color)
            };
        } else if (piece_type == mylibrary::J) {
            piece_ = std::vector<Segment>{
                    Segment((location + mylibrary::Location(0, 0)) % Location(height_,width_), color),
                    Segment((location + mylibrary::Location(1, 0)) % Location(height_,width_), color),
                    Segment((location + mylibrary::Location(1, 1)) % Location(height_,width_), color),
                    Segment((location + mylibrary::Location(1, 2)) % Location(height_,width_), color)
            };
        } else {
            piece_ = std::vector<Segment>{
                Segment((location + mylibrary::Location(0, 2)) % Location(height_,width_), color),
                Segment((location + mylibrary::Location(0, 1)) % Location(height_,width_), color),
                Segment((location + mylibrary::Location(0, 0)) % Location(height_,width_), color),
                Segment((location + mylibrary::Location(1, 0)) % Location(height_,width_), color)
        };
        }
    }

    Engine::Engine(size_t width, size_t height) : width_{width},
                                                  height_{height},
                                                  direction_{Direction::kStill}
                                                  {Reset();}

    /**
     * Converts a direction into a delta location.
     */
    Location FromDirection(const Direction direction) {
        switch (direction) {
            case Direction::kLeft:
                return {-1, 0};
            case Direction::kRight:
                return {+1, 0};
            case Direction::kDown:
                return {0, -1};
            case Direction::kUp:
                return {0, +1};
            case Direction::kStill:
                return {0,0};
        }
    }

    void Engine::Step() {
        Location d_loc = FromDirection(direction_);
        const std::vector<Location> old_occupied_tiles = GetOccupiedTiles();

        for (Segment& block : piece_) {
            Location next = (block.GetLocation() + d_loc) % Location(height_, width_);
            block.SetLocation(next);
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

        for (size_t row = 0; row < height_; ++row) {
            for (size_t col = 0; col < width_; ++col) {
                Location loc(row, col);
                int count = 0;
                for (int i = 0; i < occupied_tiles.size(); ++i) {
                    if (occupied_tiles[i] == loc) ++count;
                }
                if (count == 0) {
                    return loc;
                }
            }
        }
    }

    Color Engine::GetRandomColor() {
        return blue;
    }

    Piece Engine::GetRandomPieceType() {
        return L;
    }

    void Engine::SetDirection(Direction direction) {
        direction_ = direction;
    }
}