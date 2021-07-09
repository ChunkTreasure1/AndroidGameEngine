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

bool Input::IsKeyReleased(SDL_KeyCode keyCode)
{
    const Uint8* keyState = SDL_GetKeyboardState(NULL);

    return !keyState[keyCode];
}