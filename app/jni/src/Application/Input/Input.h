//
// Created by xXRag on 2021-07-08.
//

#ifndef TESTPROJECT_INPUT_H
#define TESTPROJECT_INPUT_H

#include <cstdint>
#include <SDL_keycode.h>
#include <glm/glm.hpp>

class Input
{
public:
    static bool IsKeyPressed(int keyCode);
    static bool IsKeyReleased(int keyCode);

    static bool IsMouseButtonPressed(uint32_t button);
    static bool IsMouseButtonReleased(uint32_t button);

    static const glm::vec2& GetMousePosition();
};


#endif //TESTPROJECT_INPUT_H
