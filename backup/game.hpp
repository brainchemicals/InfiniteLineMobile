#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <vector>
#include <iostream>

struct Cell : SDL_Rect
{
    SDL_Texture *cellTexture = nullptr;
    SDL_Texture *cellValueTexture = nullptr;
    SDL_Rect cellValueRect{120, 120, 110, 110};

    int x = 0;
    int y = 0;
    int w = 120;
    int h = 120;

    int cellValue{0};
    int cellValueLength{0};
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
    int keyPressed{15};
};

struct Display
{
    const int TEXTWIDTH{55};
    const int MAXDIGITS{6}; // includes '-'
    const int MAXINPUT{5};
    SDL_Texture *displayTexture = nullptr;
    SDL_Rect numberDisplayRect{0};
    SDL_Rect displayBorder{
        0, 0,
        TEXTWIDTH *MAXDIGITS, 100};

    Uint8 lengthOfDisplay{1};
    char myText[5]{'0'};
    int myTextToInt{0};
};

enum State
{
    GAME_WAITING,
    GAME_GRIDINPUT,
    GAME_TYPING,
};

enum namedKey
{
    KEY_ONE = 0,
    KEY_TWO,
    KEY_THREE,
    KEY_ZERO,
    KEY_MINUS,
    KEY_FOUR,
    KEY_FIVE,
    KEY_SIX,
    KEY_AC,
    KEY_PLUS,
    KEY_SEVEN,
    KEY_EIGHT,
    KEY_NINE,
    KEY_BACK,
    KEY_OK,
    KEY_EMPTY
};

enum middleNumbers
{
    LEFT_UP = 14,
    RIGHT_UP,
    LEFT_DOWN = 20,
    RIGHT_DOWN
};

class CGame;
class CKey
{
  private:
  public:
    std::vector<std::string> files{};
    SDL_Texture *keyTexture = nullptr;
    SDL_Rect keyRect{
        -120, -120,
        120, 120};

    SDL_Texture *debugText = nullptr;

    bool keyDebug{false};

    const Uint8 KEYWIDTH{120};
    int value{0};
    char kind{'8'};
    unsigned char keypos{0};
    // int keyPressed{14};
    //bool keyPressed{false};

    void LoadKeys(
        SDL_Renderer *renderer,
        SDL_Rect gridRect,
        Keypad &keypad);
    // either use a number
    // or use a kind
    void DoKey(unsigned int key);
    void DoKey(char kind);
};

class CGrid
{
    // methods for filling answer
    std::vector<Cell> answerGrid{0};
    int Sum(int a, int b);
    int Total(int a, int b);
    void InitUp(int column);
    void InitDown(int column);
    void InitLeft(int row);
    void InitRight(int row);

    //void StartGrid();

    // return position of error
    void HiddenAnswerGrid();
    int CheckGrid();

  public:
    SDL_Rect gridArea{0};
    SDL_Texture *selectTexture = nullptr;

    bool gridDebug{false};

    const Uint8 CELLWIDTH{120};
    const Uint8 VALUEWIDTH{100};
    const Uint8 GRIDWIDTH{6};
    unsigned int selected{0};
    std::vector<Cell> grid{};

    int w{1};
    int x{2};
    int y{3};
    int z{4};
    /*
    int w{1};
    const int wX{120*3};
    const int wY{120*3};
    int x{2};
    const int xX{120*4};
    const int xY{120*3};
    int y{3};
    const int yX{120*3};
    const int yY{120*4};
    int z{4};
    const int zX{120*4};
    const int zY{120*4};
    */

    void LoadGrid(SDL_Renderer *renderer);
    void SelectedCell(
        SDL_Rect r, SDL_Rect g);
    void PutGrid(
        SDL_Renderer *renderer,
        const Display display);

    void LoadAnswerGrid(SDL_Renderer *renderer);
    bool GridComplete();
};

class CGame : public CGrid, public CKey
{
  public:
    CGame()
    {
    }
    ~CGame()
    {
        QuitGame();
    }

    SDL_Event event{};
    SDL_TouchFingerEvent f{};
    SDL_Rect touch{1, 1, 1, 1};
    SDL_Rect debugRect{720, 0, 40, 40};

    bool gameDebug{false};

    Keypad keypad{};
    Display display{};

    int InitSDL();
    int Run();

    //===============
    //Helpers
    //void HelpGridLoad(SDL_Renderer *renderer);
    void HelpGridLoad();
    void HelpPutGrid();
    void HelpGridDisplay();
    void HelpKeypadLoad(
        SDL_Renderer *renderer,
        SDL_Rect rect,
        Keypad &keypad);
    void HelpKeypadDisplay();
    void HelpDisplayLoad();
    void HelpDisplayDisplay();
    void HelpAnswerGrid();
    //===============
  private:
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    bool loopgame = true;
    int screenWidth{0};
    int screenHeight{0};

    void InputGame();
    void UpdateScreen();

    void HandleUI();
    void PositionGrid(int offset);
    void TouchingGrid();
    void TouchingKey(int i);

    void QuitGame();

    int GetOrientation();
    int GetScreenSize();
};