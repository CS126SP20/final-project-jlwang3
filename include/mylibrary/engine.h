//
// Created by Jeffrey Wang on 4/22/20.
//

#ifndef FINALPROJECT_ENGINE_H
#define FINALPROJECT_ENGINE_H

#include <cstdio>

namespace mylibrary {
    /**
     * The engine should enforce the fact that pieces do not overlap and do not go outside the boundary.
     */
     class Engine {
     public:
         void Reset();

     private:
         const size_t board_size_ = 10;
     };

}
#endif //FINALPROJECT_ENGINE_H
