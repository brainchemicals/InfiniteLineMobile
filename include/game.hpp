#include <SDL2/SDL.h>

#include <SDL2/SDL_ttf.h>

#include <SDL2/SDL_image.h>

#include <iostream>

class Game

{

  public:

    Game()

    {

    }

    // all keypad keys

    SDL_Texture *key0 = nullptr;

    SDL_Texture *key0H = nullptr;

    SDL_Texture *key0temp = nullptr;

    SDL_Texture *key1 = nullptr;

    SDL_Texture *key1H = nullptr;

    SDL_Texture *key1temp = nullptr;

    SDL_Texture *key2 = nullptr;

    SDL_Texture *key2H = nullptr;

    SDL_Texture *key2temp = nullptr;

    SDL_Texture *key3 = nullptr;

    SDL_Texture *key3H = nullptr;

    SDL_Texture *key3temp = nullptr;

    SDL_Texture *key4 = nullptr;

    SDL_Texture *key4H = nullptr;

    SDL_Texture *key4temp = nullptr;

    SDL_Texture *key5 = nullptr;

    SDL_Texture *key5H = nullptr;

    SDL_Texture *key5temp = nullptr;

    SDL_Texture *key6 = nullptr;

    SDL_Texture *key6H = nullptr;

    SDL_Texture *key6temp = nullptr;

    SDL_Texture *key7 = nullptr;

    SDL_Texture *key7H = nullptr;

    SDL_Texture *key7temp = nullptr;

    SDL_Texture *key8 = nullptr;

    SDL_Texture *key8H = nullptr;

    SDL_Texture *key8temp = nullptr;

    SDL_Texture *key9= nullptr;

    SDL_Texture *key9H = nullptr;

    SDL_Texture *key9temp = nullptr;

    SDL_Texture *keyback = nullptr;

    SDL_Texture *keybackH = nullptr;

    SDL_Texture *keybacktemp = nullptr;

    SDL_Texture *keyok = nullptr;

    SDL_Texture *keyokH = nullptr;

    SDL_Texture *keyoktemp = nullptr;

    SDL_Texture *textTexture = nullptr;

    SDL_Window *window = nullptr;

    SDL_Renderer *renderer = nullptr;

    int screenWidth{0};

    int screenHeight{0};

    SDL_bool isLooping{SDL_TRUE};

    SDL_Rect touch{};

    SDL_Rect quit{};

    SDL_Rect input{};

    // keypad

    SDL_Rect key0Rect{0};

    SDL_Rect key1Rect{0};

    SDL_Rect key2Rect{0};

    SDL_Rect key3Rect{0};

    SDL_Rect key4Rect{0};

    SDL_Rect key5Rect{0};

    SDL_Rect key6Rect{0};

    SDL_Rect key7Rect{0};

    SDL_Rect key8Rect{0};

    SDL_Rect key9Rect{0};

    SDL_Rect keybackRect{0};

    SDL_Rect keyokRect{0};

    char myText[7] = {'\0'};

    SDL_Texture *loadImage(SDL_Renderer *renderer, const char *path);

    SDL_Texture *loadText(SDL_Renderer *renderer, const char *text);

    int InitSDL();

    void QuitSDL();

    void deleteGFX();

    void loadRect();

    void gameLoop();

    void validateInput();

    void highlightKey(SDL_Texture *keyTexture);

    void unhighlightKey(

        SDL_Texture *keyTexture);

    void displayText();

    void MakeGrid(int sw, int sh);

};
