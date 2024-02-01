/*
name: Infinite Line
description: number puzzle containing four
values in the centre and the directional
nurmeric difference is added on top
author: Kevin Barnard

Copyright (c) 2023 Brainchemicals

This attempt at IL will be to separate
the two halfs of the screen. Grid input and the keypad. Both grid and keypad
work together with the text input in the middle.

also I wanted portrait and landscape modes.

in this version the keypad will always be
towards the top of the phone in
landscape mode 

this version can handle a keypress
and a moving a finger due with TOUCHMOTION

work in progress
bugs?
sometimes the grid will turn green with
no input entered. HelpPutGrid and PutGrid
only are called when OK is pressed
unless AnswerGrid blurs with the user grid

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
