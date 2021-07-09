//
// Created by xXRag on 2021-07-08.
//

#ifndef TESTPROJECT_INPUT_H
#define TESTPROJECT_INPUT_H

#include <cstdint>
#include <SDL_keycode.h>

class Input
{
public:
    static bool IsKeyPressed(int keyCode);
    static bool IsKeyReleased(SDL_KeyCode keyCode);
};


#endif //TESTPROJECT_INPUT_H
