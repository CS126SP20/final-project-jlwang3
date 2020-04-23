//
// Created by Jeffrey Wang on 4/22/20.
//
#include <mylibrary/location.h>

#ifndef FINALPROJECT_SEGMENT_H
#define FINALPROJECT_SEGMENT_H
namespace mylibrary {
    enum Color { red, blue, yellow };
    class Segment {
    public:
        explicit Segment(const Location& location, Color color);

        Location GetLocation() const;
        Location SetLocation(const Location&);
        Color GetColor();
        Color SetColor(Color);

    private:
        Location location_;
        Color color_;
    };
}
#endif //FINALPROJECT_SEGMENT_H
