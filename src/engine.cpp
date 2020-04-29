//
// Created by Jeffrey Wang on 4/22/20.
//

#include <mylibrary/engine.h>
#include <mylibrary/piece.h>
#include <vector>
#include <utility>

namespace mylibrary {

    std::vector<Segment> Engine::GetCurrentPiece() const {
        return current_piece_;
    }

    void Engine::NewPiece() {
        current_piece_ = {};
        Location location = GetRandomLocation();
        Color color = GetRandomColor();
        Piece piece_type = GetRandomPieceType();
        if (piece_type == mylibrary::I) {
            current_piece_ = std::vector<Segment>{Segment((location + mylibrary::Location(0, 0)) % Location(width_, height_), color),
                                 Segment((location + mylibrary::Location(0,1)) % Location(width_,height_), color),
                                 Segment((location + mylibrary::Location(0,2)) % Location(width_,height_), color),
                                 Segment((location + mylibrary::Location(0,3)) % Location(width_,height_), color)};
        } else if (piece_type == mylibrary::O) {
            current_piece_ = std::vector<Segment>{
                    Segment((location + mylibrary::Location(0,0)) % Location(width_,height_), color),
                    Segment((location + mylibrary::Location(1, 0)) % Location(width_,height_), color),
                    Segment((location + mylibrary::Location(0, 1)) % Location(width_,height_), color),
                    Segment((location + mylibrary::Location(1, 1)) % Location(width_,height_), color)
            };
        } else if (piece_type == mylibrary::T) {
            current_piece_ = std::vector<Segment>{
                    Segment((location + mylibrary::Location(0,0)) % Location(width_,height_), color),
                    Segment((location + mylibrary::Location(1, 0)) % Location(width_,height_), color),
                    Segment((location + mylibrary::Location(2, 0)) % Location(width_,height_), color),
                    Segment((location + mylibrary::Location(1, 1)) % Location(width_,height_), color)
            };
        } else if (piece_type == mylibrary::S) {
            current_piece_ = std::vector<Segment>{
                    Segment((location + mylibrary::Location(0, 0)) % Location(width_,height_), color),
                    Segment((location + mylibrary::Location(1, 0)) % Location(width_,height_), color),
                    Segment((location + mylibrary::Location(1, 1)) % Location(width_,height_), color),
                    Segment((location + mylibrary::Location(2, 1)) % Location(width_,height_), color)
            };
        } else if (piece_type == mylibrary::Z) {
            current_piece_ = std::vector<Segment>{
                    Segment((location + mylibrary::Location(0, 1)) % Location(width_,height_), color),
                    Segment((location + mylibrary::Location(1, 1)) % Location(width_,height_), color),
                    Segment((location + mylibrary::Location(1, 0)) % Location(width_,height_), color),
                    Segment((location + mylibrary::Location(2, 0)) % Location(width_,height_), color)
            };
        } else if (piece_type == mylibrary::J) {
            current_piece_ = std::vector<Segment>{
                    Segment((location + mylibrary::Location(0, 0)) % Location(width_,height_), color),
                    Segment((location + mylibrary::Location(1, 0)) % Location(width_,height_), color),
                    Segment((location + mylibrary::Location(1, 1)) % Location(width_,height_), color),
                    Segment((location + mylibrary::Location(1, 2)) % Location(width_,height_), color)
            };
        } else {
            current_piece_ = std::vector<Segment>{
                Segment((location + mylibrary::Location(0, 2)) % Location(width_,height_), color),
                Segment((location + mylibrary::Location(0, 1)) % Location(width_,height_), color),
                Segment((location + mylibrary::Location(0, 0)) % Location(width_,height_), color),
                Segment((location + mylibrary::Location(1, 0)) % Location(width_,height_), color)
        };
        }
    }

    Engine::Engine(size_t width, size_t height) : width_{width},
                                                  height_{height},
                                                  direction_{Direction::kDown}
                                                  { NewPiece();}

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
                return {0, +1};
        }
    }

    void Engine::Step() {
        Location d_loc = FromDirection(direction_);
        const std::vector<Location> old_occupied_tiles = GetCurrentOccupiedTiles();

        for (Segment& block : current_piece_) {
            Location next = (block.GetLocation() + d_loc) % Location(width_,height_);
            block.SetLocation(next);
        }
    }

    std::vector<Location> Engine::GetCurrentOccupiedTiles() {
        std::vector<Location> occupied_tiles;

        for (const Segment& part : current_piece_) {
            occupied_tiles.push_back(part.GetLocation());
        }

        return occupied_tiles;
    }

    Location Engine::GetRandomLocation() {
        int corresponding_location_ = RandomInt(1,width_);
        return mylibrary::Location(corresponding_location_ - 1,-1);
    }

    Color Engine::GetRandomColor() {
        int corresponding_color_ = RandomInt(1,3);
        if (corresponding_color_ == 1) return red;
        if (corresponding_color_ == 2) return green;
        return blue;
    }

    Piece Engine::GetRandomPieceType() {
        int corresponding_piece_type_ = RandomInt(1,7);
        if (corresponding_piece_type_ == 1) return I;
        if (corresponding_piece_type_ == 2) return O;
        if (corresponding_piece_type_ == 3) return T;
        if (corresponding_piece_type_ == 4) return S;
        if (corresponding_piece_type_ == 5) return Z;
        if (corresponding_piece_type_ == 6) return J;
        return L;
    }

    void Engine::SetDirection(Direction direction) {
        direction_ = direction;
    }

    bool Engine::IsTouchingBottom() {
        for (int i = 0; i < current_piece_.size(); ++i) {
            if (current_piece_[i].GetLocation().Col() == height_ - 1) return true;
        }
        return false;
    }

    int Engine::RandomInt(int a, int b) {
        std::mt19937 gen_(rd_());
        std::uniform_int_distribution<> dis_(a, b);
        return dis_(gen_);
    }

    void Engine::Reset() {
        current_piece_ = {};
        all_pieces_ = {};
        occupied_tiles_ = {};
        NewPiece();
    }
}