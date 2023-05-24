#include "game.hpp"

SDL_Texture *Game::loadText(SDL_Renderer *renderer, const char *text)

{

    if (text == NULL)

    {

        std::string db = "loadText Error: Null text";

        SDL_ShowSimpleMessageBox(

            SDL_MESSAGEBOX_ERROR,

            "title",

            db.c_str(),

            NULL);

    }

    if (TTF_Init() == -1)

    {

        std::string db = "loadText Error: TTF_Init Error";

        SDL_ShowSimpleMessageBox(

            SDL_MESSAGEBOX_ERROR,

            "title",

            db.c_str(),

            NULL);

        return NULL;

    }

    TTF_Font *font = TTF_OpenFont("/system/fonts/Roboto-Regular.ttf", 256);

    if (font == NULL)

    {

        std::string db = "loadText Error: TTF_OpenFont Error";

        SDL_ShowSimpleMessageBox(

            SDL_MESSAGEBOX_ERROR,

            "title",

            db.c_str(),

            NULL);

        return NULL;

    }

    SDL_Color color = {255, 255, 255};

    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);

    if (surface == NULL)

    {

        std::string db = "loadText Error: Surface NULL";

        SDL_ShowSimpleMessageBox(

            SDL_MESSAGEBOX_ERROR,

            "title",

            db.c_str(),

            NULL);

    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);

    if (texture == NULL)

    {

        std::string db = "loadText Error: Texture NULL";

        SDL_ShowSimpleMessageBox(

            SDL_MESSAGEBOX_ERROR,

            "title",

            db.c_str(),

            NULL);

        return NULL;

    }

    return texture;

}

SDL_Texture *Game::loadImage(SDL_Renderer *renderer, const char *path)

{

    SDL_Surface *img = IMG_Load(path);

    if (img == NULL)

    {

        std::string db = "loadImg Error: Surface NULL";

        db += path;

        db = SDL_GetError();

        SDL_ShowSimpleMessageBox(

            SDL_MESSAGEBOX_ERROR,

            "title",

            db.c_str(),

            NULL);

        return NULL;

    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, img);

    SDL_FreeSurface(img);

    if (texture == NULL)

    {

        std::string db = "loadImage Error: Texture NULL";

        SDL_ShowSimpleMessageBox(

            SDL_MESSAGEBOX_ERROR,

            "title",

            db.c_str(),

            NULL);

        return NULL;

    }

    return texture;

}

int Game::InitSDL()

{

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)

    {

        return 1;

    }

    window = SDL_CreateWindow("Hello SDL2-ttf", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);

    if (window == NULL)

    {

        return 1;

    }

    renderer = SDL_CreateRenderer(window, -1, 0);

    if (renderer == NULL)

    {

        return 1;

    }

    // it worked

    SDL_GetRendererOutputSize(renderer, &screenWidth, &screenHeight);

    //IMG_Init(IMG_INIT_PNG);

    return 0;

}

void Game::QuitSDL()

{

    SDL_DestroyRenderer(renderer);

    SDL_DestroyWindow(window);

    //IMG_Quit();

    SDL_Quit();

}

void Game::deleteGFX()

{

    SDL_DestroyTexture(key1);

    SDL_DestroyTexture(key1H);

    SDL_DestroyTexture(key2);

    SDL_DestroyTexture(key2H);

    SDL_DestroyTexture(key3);

    SDL_DestroyTexture(key3H);

    SDL_DestroyTexture(key4);

    SDL_DestroyTexture(key4H);

    SDL_DestroyTexture(key5);

    SDL_DestroyTexture(key5H);

    SDL_DestroyTexture(key6);

    SDL_DestroyTexture(key6H);

    SDL_DestroyTexture(key7);

    SDL_DestroyTexture(key7H);

    SDL_DestroyTexture(key8);

    SDL_DestroyTexture(key8H);

    SDL_DestroyTexture(key9);

    SDL_DestroyTexture(key9H);

    SDL_DestroyTexture(keyback);

    SDL_DestroyTexture(keybackH);

    SDL_DestroyTexture(keyok);

    SDL_DestroyTexture(keyokH);

    SDL_DestroyTexture(textTexture);

}

void Game::loadRect()

{

    touch.x = 0;

    touch.y = 0;

    touch.w = 1;

    touch.h = 1;

    input.x = 0;

    input.y = 0;

    input.h = 300;

    input.w = screenWidth;

    quit.x = 0;

    quit.y = 300;

    quit.h = 300;

    quit.w = screenWidth;

    // testing keypad gfx

    key1Rect.w = 150;

    key1Rect.h = 150;

    key1Rect.x = 150;

    key1Rect.y = 700;

    key2Rect.w = 150;

    key2Rect.h = 150;

    key2Rect.x = 300;

    key2Rect.y = 700;

    key3Rect.w = 150;

    key3Rect.h = 150;

    key3Rect.x = 450;

    key3Rect.y = 700;

    key4Rect.w = 150;

    key4Rect.h = 150;

    key4Rect.x = 150;

    key4Rect.y = 850;

    key5Rect.w = 150;

    key5Rect.h = 150;

    key5Rect.x = 300;

    key5Rect.y = 850;

    key6Rect.w = 150;

    key6Rect.h = 150;

    key6Rect.x = 450;

    key6Rect.y = 850;

    key7Rect.w = 150;

    key7Rect.h = 150;

    key7Rect.x = 150;

    key7Rect.y = 1000;

    key8Rect.w = 150;

    key8Rect.h = 150;

    key8Rect.x = 300;

    key8Rect.y = 1000;

    key9Rect.w = 150;

    key9Rect.h = 150;

    key9Rect.x = 450;

    key9Rect.y = 1000;

    

    key0Rect.w = 150;

    key0Rect.h = 150;

    key0Rect.x = 300;

    key0Rect.y = 1150;

    

    keybackRect.w = 150;

    keybackRect.h = 150;

    keybackRect.x = 450;

    keybackRect.y = 1150;

    

    keyokRect.w = 150;

    keyokRect.h = 150;

    keyokRect.x = 150;

    keyokRect.y = 1150;

}

void Game::MakeGrid(int sw, int sh)

{

    key1 = loadImage(

        renderer, "imgs/key1.png");

    key1H = loadImage(

        renderer, "imgs/key1H.png");

    key2 = loadImage(

        renderer, "imgs/key2.png");

    key2H = loadImage(

        renderer, "imgs/key2H.png");

    key3 = loadImage(

        renderer, "imgs/key3.png");

    key3H = loadImage(

        renderer, "imgs/key3H.png");

    key4 = loadImage(

        renderer, "imgs/key4.png");

    key4H = loadImage(

        renderer, "imgs/key4H.png");

    key5 = loadImage(

        renderer, "imgs/key5.png");

    key5H = loadImage(

        renderer, "imgs/key5H.png");

    key6 = loadImage(

        renderer, "imgs/key6.png");

    key6H = loadImage(

        renderer, "imgs/key6H.png");

    key7 = loadImage(

        renderer, "imgs/key7.png");

    key7H = loadImage(

        renderer, "imgs/key7H.png");

    key8 = loadImage(

        renderer, "imgs/key8.png");

    key8H = loadImage(

        renderer, "imgs/key8H.png");

    key9 = loadImage(

        renderer, "imgs/key9.png");

    key9H = loadImage(

        renderer, "imgs/key9H.png");

    key0 = loadImage(

        renderer, "imgs/key0.png");

    key0H = loadImage(

        renderer, "imgs/key0H.png");

    keyback = loadImage(

        renderer, "imgs/keyback.png");

    keybackH = loadImage(

        renderer, "imgs/keybackH.png");

    keyok = loadImage(

        renderer, "imgs/keyok.png");

    keyokH = loadImage(

        renderer, "imgs/keyokH.png");

}

void Game::validateInput()

{

    // no input

    if (myText[0] == '\0')

    {

        strcpy(myText, "N/A");

        return;

    }

    // any 000025 number

    // and ignore characters

    try

    {

        int i = std::stoi(myText);

        std::string s = std::to_string(i);

        strcpy(myText, s.c_str());

    }

    catch (std::invalid_argument &err)

    {

        strcpy(myText, "N/A");

    }

}

void Game::displayText()

{

    // first make it sensible input

    validateInput();

    SDL_SetHint(

        SDL_HINT_RENDER_SCALE_QUALITY, "2");

    textTexture = loadText(renderer, myText);

    // set values for displaying answer

    int tw, th;

    SDL_QueryTexture(textTexture, NULL, NULL, &tw, &th);

    SDL_Rect dest;

    // Our text always has width much bigger than height, use this

    dest.x = 0;

    dest.w = screenWidth;

    dest.h = th * screenWidth / tw;

    dest.y = (screenHeight - dest.h) / 2;

    // present final answer

    SDL_SetRenderDrawColor(renderer,

                           0, 150, 0, 255);

    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, textTexture, NULL, &dest);

    SDL_RenderPresent(renderer);

    SDL_Delay(5000);

}

void Game::gameLoop()

{

    SDL_Event e{};

    SDL_TextInputEvent t{};

    while (SDL_PollEvent(&e) != 0)

    {

        SDL_TouchFingerEvent f{};

        switch (e.type)

        {

        case SDL_FINGERDOWN:

        {

            f = e.tfinger;

            touch.x = f.x * screenWidth;

            touch.y = f.y * screenHeight;

            touch.w = 1;

            touch.h = 1;

            if (SDL_HasIntersection(&touch, &key1Rect))

            {

                // store unhighlighted key

                key1temp = key1;

                // show highlight

                key1 = key1H;

            }

            if (SDL_HasIntersection(&touch,

                                    &key2Rect))

            {

                key2temp = key2;

                key2 = key2H;

            }

            if (SDL_HasIntersection(&touch,

                                    &key3Rect))

            {

                key3temp = key3;

                key3 = key3H;

            }

            if (SDL_HasIntersection(&touch,

                                    &key4Rect))

            {

                key4temp = key4;

                key4 = key4H;

            }

            if (SDL_HasIntersection(&touch,

                                    &key5Rect))

            {

                key5temp = key5;

                key5 = key5H;

            }

            if (SDL_HasIntersection(&touch,

                                    &key6Rect))

            {

                key6temp = key6;

                key6 = key6H;

            }

            if (SDL_HasIntersection(&touch,

                                    &key7Rect))

            {

                key7temp = key7;

                key7 = key7H;

            }

            if (SDL_HasIntersection(&touch,

                                    &key8Rect))

            {

                key8temp = key8;

                key8 = key8H;

            }

            if (SDL_HasIntersection(&touch,

                                    &key9Rect))

            {

                key9temp = key9;

                key9 = key9H;

            }

            if (SDL_HasIntersection(&touch,

                &keybackRect))

            {

                keybacktemp = keyback;

                keyback = keybackH;

            }

            break;

        }

        case SDL_FINGERUP:

        {

            f = e.tfinger;

            touch.x = f.x * screenWidth;

            touch.y = f.y * screenHeight;

            touch.w = 1;

            touch.h = 1;

            if (SDL_HasIntersection(&touch, &quit))

            {

                isLooping = SDL_FALSE;

            }

            if (SDL_HasIntersection(&touch, &input))

            {

                SDL_StartTextInput();

            }

            if (SDL_HasIntersection(&touch, &key1Rect))

            {

                key1 = key1temp;

                strcat(myText, "1");

            }

            if (SDL_HasIntersection(&touch,

                                    &key2Rect))

            {

                key2 = key2temp;

                strcat(myText, "2");

            }

            if (SDL_HasIntersection(&touch,

                                    &key3Rect))

            {

                key3 = key3temp;

                strcat(myText, "3");

            }

            if (SDL_HasIntersection(&touch,

                                    &key4Rect))

            {

                key4 = key4temp;

                strcat(myText, "4");

            }

            if (SDL_HasIntersection(&touch,

                                    &key5Rect))

            {

                key5 = key5temp;

                strcat(myText, "5");

            }

            if (SDL_HasIntersection(&touch,

                                    &key6Rect))

            {

                key6 = key6temp;

                strcat(myText, "6");

            }

            if (SDL_HasIntersection(&touch,

                                    &key7Rect))

            {

                key7 = key7temp;

                strcat(myText, "7");

            }

            if (SDL_HasIntersection(&touch,

                                    &key8Rect))

            {

                key8 = key8temp;

                strcat(myText, "8");

            }

            if (SDL_HasIntersection(&touch,

                                    &key9Rect))

            {

                key9 = key9temp;

                strcat(myText, "9");

            }

            if (SDL_HasIntersection(&touch,

                &keybackRect))

            {

                keyback = keybacktemp;

                std::string s = myText;

                s.pop_back();

                strcpy(myText, s.c_str());

            }

            break;

        }

        case SDL_TEXTINPUT:

        {

            // read input once

            t = e.text;

            //myText = t.text;

            // concatenate!

            strcat(myText, t.text);

            //stoi will cut leading zeros

            break;

        }

        default:

        {

            if (e.key.keysym.sym == SDL_GetKeyFromScancode(SDL_SCANCODE_RETURN))

            {

                isLooping = SDL_FALSE;

            }

            break;

        }

        }

    }

    // update screen

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    SDL_RenderClear(renderer);

    // input box

    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);

    SDL_RenderFillRect(renderer, &input);

    // quitbox

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

    SDL_RenderFillRect(renderer, &quit);

    // test keypad

    SDL_RenderCopy(renderer, key1, NULL,

                   &key1Rect);

    SDL_RenderCopy(renderer, key2, NULL,

                   &key2Rect);

    SDL_RenderCopy(renderer, key3, NULL,

                   &key3Rect);

    SDL_RenderCopy(renderer, key4, NULL,

                   &key4Rect);

    SDL_RenderCopy(renderer, key5, NULL,

                   &key5Rect);

    SDL_RenderCopy(renderer, key6, NULL,

                   &key6Rect);

    SDL_RenderCopy(renderer, key7, NULL,

                   &key7Rect);

    SDL_RenderCopy(renderer, key8, NULL,

                   &key8Rect);

    SDL_RenderCopy(renderer, key9, NULL,

                   &key9Rect);

    SDL_RenderCopy(renderer, key0, NULL,

        &key0Rect);

    SDL_RenderCopy(renderer, keyback, NULL,

        &keybackRect);

    SDL_RenderCopy(renderer, keyok, NULL,

        &keyokRect);

    SDL_RenderPresent(renderer);

}

//

// Main.cpp

//

int main(int argc, char *argv[])

{

    Game game{};

    if (game.InitSDL() != 0)

        return 1;

    game.loadRect();

    SDL_SetTextInputRect(&game.input);

    // keypad test

    game.MakeGrid(1, 1);

    while (game.isLooping)

    {

        game.gameLoop();

    }

    SDL_StopTextInput();

    game.displayText();

    // quit everything

    game.deleteGFX();

    game.QuitSDL();

    return 0;

}
