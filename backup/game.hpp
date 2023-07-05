#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <vector>
#include <iostream>

struct Cell : SDL_Rect
{
    SDL_Texture *cellTexture = nullptr;
    SDL_Texture *cellValueTexture = nullptr;
    int x = 0;
    int y = 0;
    int w = 120;
    int h = 120;
    int cellValue{0};
    unsigned int cellPos{0};
    bool cellSelected{false};
};

// forward declaration
class CKey;
struct Keypad
{
    std::vector<CKey> keys{};
    SDL_Rect fullKeypadRect{0};
    SDL_Texture *keyHighlight = nullptr;
    int keyPressed{14};
};

struct Display
{
    const int TEXTWIDTH{55};
    const int MAXDIGITS{5};
    SDL_Texture *displayTexture = nullptr;
    SDL_Rect numberDisplayRect{0};
    //char myText{'0'};
    Uint8 lengthOfDisplay{1};
    char myText[5]{'0'};
    int myTextInt{0};
};

enum State
{
    GAME_WAITING,
    GAME_GRIDINPUT,
    GAME_TYPING,
};

enum KeyValue
{
    KEY_ZERO = 0,
    KEY_ONE,
    KEY_TWO,
    KEY_THREE,
    KEY_FOUR,
    KEY_FIVE,
    KEY_SIX,
    KEY_SEVEN,
    KEY_EIGHT,
    KEY_NINE
};

class CGame;
class CKey
{
  public:
    std::vector<std::string> files{};
    SDL_Texture *keyTexture = nullptr;
    SDL_Rect keyRect{0,0,120,120};
    
    SDL_Texture* debugText = nullptr;

    int value{0};
    char kind{'8'};
    unsigned char keypos{0};
   // int keyPressed{14};
    //bool keyPressed{false};

    void LoadKeys(
        SDL_Renderer *renderer,
        SDL_Rect gridRect,
        Keypad& keypad);
    // either use a number
    // or use a kind
    void DoKey(unsigned int key);
    void DoKey(char kind);
};

class CGrid
{
    // clear grid
    // add up grid

  public:
    SDL_Rect gridArea{0};
    SDL_Texture *selectTexture = nullptr;
    unsigned int selected{0};
    std::vector<Cell> grid{};

    void LoadGrid(SDL_Renderer *renderer);
    void SelectedCell(
        SDL_Rect r, SDL_Rect g);
    //void DisplayGrid(int sw, int sh);
    // void grid complete status
};

class CGame : public CGrid, public CKey
{
  public:
    CGame()
    {
    }
    ~CGame()
    {
        //delete[5] display.myText;
        QuitGame();
    }

    SDL_Event event{};
    SDL_TouchFingerEvent f{};
    SDL_Rect touch{1, 1, 1, 1};
    SDL_Rect debugRect{720, 0, 40, 40};

    Keypad keypad{};
    Display display{};

    int InitSDL();
    int Run();

    void HelpGridLoad(SDL_Renderer *renderer);
    void HelpGridDisplay();
    void HelpKeypadLoad(
        SDL_Renderer *renderer,
        SDL_Rect rect,
        Keypad& keypad);
    void HelpKeypadDisplay();
    void HelpDisplayLoad();
    void HelpDisplayDisplay();

  private:
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    bool debug{false};
    bool loopgame = true;
    int screenWidth{0};
    int screenHeight{0};

    void HandleUI();
    void PositionGrid(int offset);
    void InputGame();
    void UpdateScreen();

    void QuitGame();
    void TouchingGrid();
    void TouchingKey(int i);

    int GetOrientation();
    int GetScreenSize();
};