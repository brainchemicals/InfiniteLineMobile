/******************

================
==                          ==
==   zlib license   ==
==                          ==
================

Copyright © 2023 Kevin "thenewkgb" Barnard

This software is provided ‘as-is’, without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3. This notice may not be removed or altered from any source
distribution.

********************/

/*
name: Infinite Line
description: number puzzle containing four
values in the centre and the directional
nurmeric difference is added on top
author: Kevin Barnard

This attempt at IL will be to separate
the two halfs of the screen. Grid input and the keypad. Both grid and keypad
work together with the text input in the middle.

also I wanted portrait and landscape modes.

in this version the keypad will always be
towards the top of the phone in
either landscape mode

this version can handle a keypress
and a moving a finger due with
different TOUCHDOWN and TOUCHUP
TOUCHMOTION

work in progress
bugs?
probably a lot
*/

#include "game.hpp"

int main(int argc, char *argv[])
{
    CGame game{};

    if (game.InitSDL() == 0)
    {
        game.Run();
    }
    else
    {
        return 1;
    }
    game.QuitGame();
    
    return 0;
}