//
// Created by Jeffrey Wang on 4/22/20.
//
#include <mylibrary/location.h>

#ifndef FINALPROJECT_SEGMENT_H
#define FINALPROJECT_SEGMENT_H
namespace mylibrary {
    class Segment {
    public:
        explicit Segment(const Location& location);
        Location GetLocation() const;
        Location SetLocation(const Location&);
        void SetVisibility(bool visible);
        bool IsVisibile() const;

    private:
        Location location_;
        bool visible_;
    };
}
#endif //FINALPROJECT_SEGMENT_H
