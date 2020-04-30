//
// Created by Jeffrey Wang on 4/22/20.
//

#include <mylibrary/engine.h>
#include <mylibrary/piece.h>
#include <vector>
#include <utility>

namespace mylibrary {

    std::vector<Segment> Engine::GetCurrentPiece() const {
        return * current_piece_;
    }

    void Engine::NewPiece() {
        current_piece_ = new std::vector<Segment>;
        Location location = GetRandomLocation();
        Color color = GetRandomColor();
        Piece piece_type = GetRandomPieceType();
        if (piece_type == mylibrary::I) {
            * current_piece_ = std::vector<Segment>{Segment((location + mylibrary::Location(0, 0)) % Location(width_, height_), color),
                                 Segment((location + mylibrary::Location(0,1)) % Location(width_,height_), color),
                                 Segment((location + mylibrary::Location(0,2)) % Location(width_,height_), color),
                                 Segment((location + mylibrary::Location(0,3)) % Location(width_,height_), color)};
        } else if (piece_type == mylibrary::O) {
            * current_piece_ = std::vector<Segment>{
                    Segment((location + mylibrary::Location(0,0)) % Location(width_,height_), color),
                    Segment((location + mylibrary::Location(1, 0)) % Location(width_,height_), color),
                    Segment((location + mylibrary::Location(0, 1)) % Location(width_,height_), color),
                    Segment((location + mylibrary::Location(1, 1)) % Location(width_,height_), color)
            };
        } else if (piece_type == mylibrary::T) {
            * current_piece_ = std::vector<Segment>{
                    Segment((location + mylibrary::Location(0,0)) % Location(width_,height_), color),
                    Segment((location + mylibrary::Location(1, 0)) % Location(width_,height_), color),
                    Segment((location + mylibrary::Location(2, 0)) % Location(width_,height_), color),
                    Segment((location + mylibrary::Location(1, 1)) % Location(width_,height_), color)
            };
        } else if (piece_type == mylibrary::S) {
            * current_piece_ = std::vector<Segment>{
                    Segment((location + mylibrary::Location(0, 0)) % Location(width_,height_), color),
                    Segment((location + mylibrary::Location(1, 0)) % Location(width_,height_), color),
                    Segment((location + mylibrary::Location(1, 1)) % Location(width_,height_), color),
                    Segment((location + mylibrary::Location(2, 1)) % Location(width_,height_), color)
            };
        } else if (piece_type == mylibrary::Z) {
            * current_piece_ = std::vector<Segment>{
                    Segment((location + mylibrary::Location(0, 1)) % Location(width_,height_), color),
                    Segment((location + mylibrary::Location(1, 0)) % Location(width_,height_), color),
                    Segment((location + mylibrary::Location(1, 1)) % Location(width_,height_), color),
                    Segment((location + mylibrary::Location(2, 0)) % Location(width_,height_), color)
            };
        } else if (piece_type == mylibrary::J) {
            * current_piece_ = std::vector<Segment>{
                    Segment((location + mylibrary::Location(0, 0)) % Location(width_,height_), color),
                    Segment((location + mylibrary::Location(1, 0)) % Location(width_,height_), color),
                    Segment((location + mylibrary::Location(1, 1)) % Location(width_,height_), color),
                    Segment((location + mylibrary::Location(1, 2)) % Location(width_,height_), color)
            };
        } else {
            * current_piece_ = std::vector<Segment>{
                Segment((location + mylibrary::Location(0, 0)) % Location(width_,height_), color),
                Segment((location + mylibrary::Location(0, 1)) % Location(width_,height_), color),
                Segment((location + mylibrary::Location(1, 0)) % Location(width_,height_), color),
                Segment((location + mylibrary::Location(0, 2)) % Location(width_,height_), color)
        };
        }
    }

    Engine::Engine(size_t width, size_t height, int difficulty) : width_{width},
                                                  height_{height},
                                                  direction_{Direction::kDown},
                                                  rotation_{Rotation::kStill},
                                                  difficulty_{difficulty}
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
        /**
         * Checks if the current piece has reached the bottom.
         * If it has, add the piece to vector storing all pieces and spawn a new piece.
         */
        if (IsTouchingBottom()) {
            for (auto i : *current_piece_) {
                all_pieces.push_back(i);
            }
            NewPiece();
        }

        /**
         * Prevent Pieces from Moving past the border
         */
        if (IsTouchingLeftSide() && direction_ == Direction::kLeft) {
            direction_ = Direction::kDown;
        }
        if (IsTouchingRightSide() && direction_ == Direction::kRight) {
            direction_ = Direction::kDown;
        }
        /**
         * Translating left and right.
         */
        Location d_loc = FromDirection(direction_);
        for (Segment& block : * current_piece_) {
            Location next = (block.GetLocation() + d_loc) % Location(width_,height_);
            /**
             * Prevents Pieces from Moving Horizontally onto each other.
             */
            for (Segment& square : all_pieces) {
                if (next == square.GetLocation()) d_loc = FromDirection(Direction::kDown);
            }
        }
        for (Segment& block : * current_piece_) {
            Location next = (block.GetLocation() + d_loc) % Location(width_,height_);
            block.SetLocation(next);
        }

        /**
         * Scoring System.
         */
        UpdateAllPieces();

        /**
         * Rotating Clockwise and Counterclockwise.
         */
         if (rotation_ == Rotation::kClockwise) {
             RotateClockwise(current_piece_);
         }
         if (rotation_ == Rotation::kCounterclockwise) {
             RotateCounterClockwise(current_piece_);
         }
    }

    bool mylibrary::Engine::IsTouchingBottom() {
        for (auto & i : *current_piece_) {
            if (i.GetLocation().Col() == height_ - 1) return true;
            for (auto & all_piece : all_pieces) {
                if (i.GetLocation().Col() == all_piece.GetLocation().Col() - 1
                && i.GetLocation().Row() == all_piece.GetLocation().Row()) return true;
            }
        }
        return false;
    }

    std::vector<mylibrary::Location> mylibrary::Engine::GetCurrentOccupiedTiles() {
        std::vector<Location> occupied_tiles;

        for (const Segment& part : * current_piece_) {
            occupied_tiles.push_back(part.GetLocation());
        }

        return occupied_tiles;
    }

    mylibrary::Location mylibrary::Engine::GetRandomLocation() {
        int corresponding_location_ = RandomInt(0,width_ - 3);
        return mylibrary::Location(corresponding_location_,0);
    }

    mylibrary::Color mylibrary::Engine::GetRandomColor() {
        int corresponding_color_ = RandomInt(1,3);
        if (corresponding_color_ == 1) return red;
        if (corresponding_color_ == 2) return green;
        return blue;
    }

    mylibrary::Piece mylibrary::Engine::GetRandomPieceType() {
        int corresponding_piece_type_ = RandomInt(1,7);
        if (corresponding_piece_type_ == 1) return I;
        if (corresponding_piece_type_ == 2) return O;
        if (corresponding_piece_type_ == 3) return T;
        if (corresponding_piece_type_ == 4) return S;
        if (corresponding_piece_type_ == 5) return Z;
        if (corresponding_piece_type_ == 6) return J;
        return L;
    }

    void mylibrary::Engine::SetDirection(Direction direction) {
        direction_ = direction;
    }

    int mylibrary::Engine::RandomInt(int a, int b) {
        std::mt19937 gen_(rd_());
        std::uniform_int_distribution<> dis_(a, b);
        return dis_(gen_);
    }

    void mylibrary::Engine::Reset() {
        current_piece_ = {};
        all_pieces = {};
        NewPiece();
        score_ = 0;
    }

    std::vector<mylibrary::Segment> mylibrary::Engine::GetAllPieces() const {
        return all_pieces;
    }

    size_t mylibrary::Engine::GetScore() {
        return score_;
    }

    void mylibrary::Engine::UpdateAllPieces() {

        std::vector<Segment> red_pieces_, green_pieces_, blue_pieces_;

        for (int i = 0; i < all_pieces.size(); ++i) {
            if (all_pieces[i].GetColor() == red) {
                red_pieces_.push_back(all_pieces[i]);
            }
            if (all_pieces[i].GetColor() == blue) {
                blue_pieces_.push_back(all_pieces[i]);
            }
            if (all_pieces[i].GetColor() == green) {
                green_pieces_.push_back(all_pieces[i]);
            }
        }

        if (NumberOfTouches(red_pieces_) >= difficulty_) {
            score_+= NumberOfTouches(red_pieces_);
            RemoveSegments(red);
            red_pieces_ = {};
        }
        if (NumberOfTouches(blue_pieces_) >= difficulty_) {
            score_+= NumberOfTouches(blue_pieces_);
            RemoveSegments(blue);
            blue_pieces_ = {};
        }
        if (NumberOfTouches(green_pieces_) >= difficulty_) {
            score_+= NumberOfTouches(green_pieces_);
            RemoveSegments(green);
            green_pieces_ = {};
        }
    }

    int mylibrary::Engine::NumberOfTouches(std::vector<Segment> piece) {
        int count = 0;
        for (int i = 0; i < piece.size(); ++i) {
            for (int j = i + 1; j < piece.size(); ++j) {
                if (piece[i].Touches(piece[j])) count++;
            }
        }
        return count;
    }

    void mylibrary::Engine::SetRotation(Rotation rotation) {
        rotation_ = rotation;
    }

    void mylibrary::Engine::RemoveSegments(Color color) {
        for (int i = all_pieces.size() - 1; i >= 0; --i) {
            if (all_pieces[i].GetColor() == color) all_pieces.erase(all_pieces.begin() + i);
        }
    }

    void mylibrary::Engine::DropAllPieces() {
        std::vector<std::vector<Segment>> remaining_pieces_;
        for (int i = 0; i < width_; ++i) {
            for (auto& piece : all_pieces) {
                if (piece.GetLocation().Row() == i) remaining_pieces_[i].push_back(piece);
            }
        }
        for (int i = 0; i < width_; ++i) {
            int count = height_ - 1;
            for (auto &segment : remaining_pieces_[i]) {
                segment.SetLocation(Location(segment.GetLocation().Row(), count));
                --count;
            }
        }
    }

    bool mylibrary::Engine::IsTouchingRightSide() {
        for (auto & i : *current_piece_) {
            if (i.GetLocation().Row() == width_ - 1) return true;
        }
        return false;
    }

    bool mylibrary::Engine::IsTouchingLeftSide() {
        for (auto & i : *current_piece_) {
            if (i.GetLocation().Row() == 0) return true;
        }
        return false;
    }

    void mylibrary::Engine::RotateClockwise(std::vector<Segment> * current_piece) {
        Location c_loc = current_piece->at(2).GetLocation();
        int can_rotate_ = 0;
        for (Segment& block : * current_piece) {
            Location next =
                    (mylibrary::Location(-(block.GetLocation() - c_loc).Col(), (block.GetLocation() - c_loc).Row()) +
                     c_loc) % Location(width_, height_);
            /**
             * Prevents Pieces from Rotating onto each other
             */
            for (Segment &square : all_pieces) {
                if (next == square.GetLocation()) ++can_rotate_ ;
            }
        }
        for (Segment &block : * current_piece) {
            Location next = (mylibrary::Location(-(block.GetLocation() - c_loc).Col(), (block.GetLocation() - c_loc).Row()) +
                             c_loc);
            if (next.IsOutOfBounds(Location(width_,height_))) ++can_rotate_;
        }
        if (can_rotate_ == 0) {
            for (Segment &block : * current_piece) {
                Location next = (mylibrary::Location(-(block.GetLocation() - c_loc).Col(), (block.GetLocation() - c_loc).Row()) +
                                 c_loc);
                block.SetLocation(next);
            }
        }
    }

    void mylibrary::Engine::RotateCounterClockwise(std::vector<Segment> * current_piece) {
        Location c_loc = current_piece->at(2).GetLocation();
        int can_rotate_ = 0;
        for (Segment &block : *current_piece) {
            Location next =
                    (mylibrary::Location((block.GetLocation() - c_loc).Col(), -(block.GetLocation() - c_loc).Row()) +
                     c_loc) % Location(width_, height_);
            /**
             * Prevents Pieces from Rotating onto each other
             */
            for (Segment &square : all_pieces) {
                if (next == square.GetLocation()) ++can_rotate_;
            }
        }
        for (Segment &block : * current_piece) {
            Location next = (mylibrary::Location(-(block.GetLocation() - c_loc).Col(), (block.GetLocation() - c_loc).Row()) +
                             c_loc);
            if (next.IsOutOfBounds(Location(width_,height_))) ++can_rotate_;
        }
        if (can_rotate_ == 0) {
            for (Segment &block : *current_piece) {
                Location next = (mylibrary::Location(-(block.GetLocation() - c_loc).Col(), (block.GetLocation() - c_loc).Row()) +
                                 c_loc);
                block.SetLocation(next);
            }
        }
    }

    bool Engine::GameOver() {
        for (auto &segment : all_pieces) {
            if (segment.GetLocation().Col() == 1) return true;
        }
        return false;
    }
}