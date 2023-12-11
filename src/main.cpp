/***********

Copyright 2023 Kevin "thenewkgb" Barnard

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
   
*************/
   
   
   
   
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
    
    return 0;
}