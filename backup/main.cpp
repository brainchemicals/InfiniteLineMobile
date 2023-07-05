/*
name: Infinite Line
author: Kevin Barnard

My next attempt at IL will be to separate
the two halfs of the screen. Grid input and the keypad with differing TOUCHUP and
TOUCHDOWN events. Both grid and keypad
work together with the text input in the middle.

also I wanted portrait and landscape modes.
in this version the keypad will always be
towards the top of the phone in landscape

this version can handle a keypress
and moving a finger due with
different TOUCHDOWN and TOUCHUP
positions
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
    
    return 0;
}