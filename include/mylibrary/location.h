//
// Created by Jeffrey Wang on 4/22/20.
//

#include <fstream>

#ifndef FINALPROJECT_LOCATION_H
#define FINALPROJECT_LOCATION_H
namespace mylibrary {
    class Location {
    public:
        Location(int row, int col);

        // Comparison operators.
        bool operator()(const Location& lhs, const Location& rhs) const;
        bool operator==(const Location& rhs) const;
        bool operator!=(const Location& rhs) const;
        bool operator<(const Location& rhs) const;
        bool operator<=(const Location& rhs) const;
        bool operator>(const Location& rhs) const;
        bool operator>=(const Location& rhs) const;

        // Vector operators.
        Location operator+(const Location& rhs) const;
        // Note: Always returns positive coordinates.
        Location operator%(const Location& rhs) const;
        Location operator-(const Location& rhs) const;
        Location& operator+=(const Location& rhs);
        Location operator-() const;

        // Accessors.
        int Row() const;
        int Col() const;

    private:
        int row_;
        int col_;
    };

    std::ostream& operator<<(std::ostream& os, const Location& location);
}
#endif //FINALPROJECT_LOCATION_H
