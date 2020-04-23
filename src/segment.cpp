//
// Created by Jeffrey Wang on 4/22/20.
//
#include <mylibrary/segment.h>

namespace mylibrary {
    Segment::Segment(const Location& location, Color color)
            : location_(location), color_(color) {}

    Location Segment::GetLocation() const { return location_; }

    Location Segment::SetLocation(const mylibrary::Location& location) {
        location_ = location;
        return location_;
    }

    Color Segment::GetColor() {
        return color_;
    }

    Color Segment::SetColor(Color color) {
        color_ = color;
        return color_;
    }
}