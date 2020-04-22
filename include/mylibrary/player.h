//
// Created by Jeffrey Wang on 4/21/20.
//

#ifndef FINALPROJECT_PLAYER_H
#define FINALPROJECT_PLAYER_H

#include <string>

namespace mylibrary {

    /**
     * Keep track of your score and name each time for a chance to enter leaderboard.
     */
    struct Player {
        Player(const std::string& name, size_t score) : name(name), score(score) {}
        std::string name;
        size_t score;
    };

}  // namespace mylibrary

#endif //FINALPROJECT_PLAYER_H
