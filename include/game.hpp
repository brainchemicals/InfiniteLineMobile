#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include <vector>
#include <iostream>

enum State
{
    //GAME_WAITING,
    //GAME_GRIDINPUT,
    //GAME_TYPING,
    // using these
    GAME_MENU,
    GAME_RUNNING,
    GAME_QUIT
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

// counting 0 to 35 for a 6x6 grid
enum middleNumbers
{
    LEFT_THREE_UP = 12,
    LEFT_TWO_UP,
    LEFT_UP,
    RIGHT_UP,
    RIGHT_TWO_UP,
    RIGHT_THREE_UP,
    LEFT_THREE_DOWN,
    LEFT_TWO_DOWN,
    LEFT_DOWN,
    RIGHT_DOWN,
    RIGHT_TWO_DOWN,
    RIGHT_THREE_DOWN
};

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
    bool cellMatch{false};
};

// forward declaration
class CKey;
struct Keypad
{
    const Uint8 KEYCOLUMNS{5};
    const Uint8 KEYROWS{3};
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
    SDL_Rect numberDisplayRect{
        0,0,TEXTWIDTH*MAXDIGITS, 100};
    SDL_Rect displayBorder{
        0, 0,
        TEXTWIDTH *MAXDIGITS, 100};

    Uint8 lengthOfDisplay{1};
    char myText[5]{'0'};
    int myTextToInt{0};
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

    int keyWidth{120};
    int value{0};
    char kind{'8'};
    unsigned char keypos{0};
    // int keyPressed{14};
    //bool keyPressed{false};

    void GrabKeySize(int sw);
    
    void LoadKeys(
        SDL_Renderer *renderer,
        SDL_Rect gridRect,
        Keypad &keypad);
    // either use a number
    // or use a kind
    // in the end not used
    void DoKey(unsigned int key);
    void DoKey(char kind);
};

class CGrid
{
    private:
    
    // methods for filling answer
    int Sum(int a, int b);
    int Total(int a, int b);
    void InitUp(int column);
    void InitDown(int column);
    void InitLeft(int row);
    void InitRight(int row);
    
    void SetWXYZ();
    // return position of error
    int CheckGrid();
    
    

  public:
    SDL_Rect gridArea{0};
    SDL_Texture *selectTexture = nullptr;
    std::vector<Cell> grid{};
std::vector<Cell> answerGrid{};

    bool gridDebug{false};
    SDL_Rect restOfScreen{};

    const Uint8 GRIDCOLUMNS{6};

    // make the grid run on any resolution
    
    int cellWidth{120};
    int valueWidth{100};
    
    
    unsigned int selected{0};
    int errorInt{-1};
    
    int high{0};
    int w{1};
    int x{2};
    int y{3};
    int z{4};
    
    void GrabGridSize(int sw);

    void LoadGrid(SDL_Renderer *renderer);
    void LoadAnswerGrid(SDL_Renderer* renderer);
    
    void SelectedCell(
        SDL_Rect r, SDL_Rect g);
    void PutGrid(
        SDL_Renderer *renderer,
        const Display display);

    bool GridComplete();
};

class Menu
{
    public:
    SDL_Texture *tMenuPortrait = nullptr;
    SDL_Texture *tMenuLandscape = nullptr;
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
    Menu menu{};
    State gameState{};

    int InitSDL();
    void Run();
    void QuitGame();

    //===============
    //Helpers
    //===============
    void HelpGridLoad();
    void HelpDisplayLoad();
    void HelpKeypadLoad(
        SDL_Renderer *renderer,
        SDL_Rect rect,
        Keypad &keypad);
        
    // passing renderer
    void HelpGridDisplay();
    void HelpKeypadDisplay();
    void HelpDisplayDisplay();
    
    void HelpPutGrid();
    void HelpAnswerGrid();
    //==========
    
    void SendSize();
    
  private:
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Rect menuButton{0,0,120,120};
    
    std::vector<int> gridLayoutX{};
    std::vector<int> gridLayoutY{};

    bool loopgame = true;
    int screenWidth{0};
    int screenHeight{0};
    int displayRatio{0};
    
    void LoadMenu();

    void InputGame();
    char InputMenu();
    void UpdateScreen();
    void UpdateMenu();

    void HandleUI();
    void PositionGrid(int offset);
    void TouchingGrid();
    void TouchingKey(int i);

    int GetOrientationAndSize();
};