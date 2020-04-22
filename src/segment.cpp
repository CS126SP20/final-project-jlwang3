//
// Created by Jeffrey Wang on 4/22/20.
//
#include <mylibrary/segment.h>

namespace mylibrary {
    Segment::Segment(const Location& location)
            : location_(location), visible_{true} {}

    Location Segment::GetLocation() const { return location_; }

    Location Segment::SetLocation(const mylibrary::Location& location) {
        location_ = location;
        return location_;
    }

    void Segment::SetVisibility(bool visible) { visible_ = visible; }

    bool Segment::IsVisibile() const { return visible_; }
}