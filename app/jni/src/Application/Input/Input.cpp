//
// Created by xXRag on 2021-07-08.
//

#include "Input.h"

#include <SDL.h>

bool Input::IsKeyPressed(int keyCode)
{
    const Uint8* keyState = SDL_GetKeyboardState(NULL);

    return keyState[keyCode];
}

bool Input::IsKeyReleased(int keyCode)
{
    const Uint8* keyState = SDL_GetKeyboardState(NULL);

    return !keyState[keyCode];
}

bool Input::IsMouseButtonPressed(uint32_t button)
{
    int x, y;
    const Uint32 mouseState = SDL_GetMouseState(&x, &y);

    return mouseState & button;
}

bool Input::IsMouseButtonReleased(uint32_t button)
{
    int x, y;
    const Uint32 mouseState = SDL_GetMouseState(&x, &y);

    return !(mouseState & button);
}

const glm::vec2 & Input::GetMousePosition()
{
    int x, y;
    SDL_GetMouseState(&x, &y);

    return glm::vec2 { (float)x, (float)y };
}