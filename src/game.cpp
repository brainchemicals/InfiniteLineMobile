#include "game.hpp"
#include <iostream>

SDL_Texture *loadText(SDL_Renderer *renderer, const char *text)
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

SDL_Texture *loadImage(SDL_Renderer *renderer, const char *path)
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

// make window fullscreen to remove
// status bar
int CGame::InitSDL()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        SDL_ShowSimpleMessageBox(
            SDL_MESSAGEBOX_ERROR,
            "Title",
            SDL_GetError(),
            NULL);
        return 1;
    }

    window = SDL_CreateWindow(
        "Inf3",
        0, 0,
        100, 100,
        SDL_WINDOW_FULLSCREEN);
    if (window == NULL)
    {
        SDL_ShowSimpleMessageBox(
            SDL_MESSAGEBOX_ERROR,
            "Title",
            SDL_GetError(),
            NULL);
        return 1;
    }

    renderer = SDL_CreateRenderer(
        window, -1, 0);
    if (renderer == NULL)
    {
        SDL_ShowSimpleMessageBox(
            SDL_MESSAGEBOX_ERROR,
            "Title",
            SDL_GetError(),
            NULL);
        return 1;
    }

    // it worked
    srand(time(0));
    return 0;
}

int CGame::Run()
{
    // get dimensions
    // for everything on screen
    GetOrientationAndSize();
    SendSize();
    
    // load gfx
    HelpGridLoad();
    HelpKeypadLoad(
        renderer,
        keypad.fullKeypadRect,
        keypad);
    HelpAnswerGrid();
    HelpDisplayDisplay();

    while (loopgame)
    {
        HandleUI();
        InputGame();
        UpdateScreen();
    }

    QuitGame();
    return 0;
}

void CGame::QuitGame()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}

int CGrid::Sum(int a, int b)
{
    return a - b;
}

int CGrid::Total(int a, int b)
{
    return a + b;
}

// InitUp first as we store w,x,y,z
void CGrid::InitUp(int where)
{
    /*
    int cellHigh = answerGrid[20].cellValue;
    int cellLow = answerGrid[14].cellValue;
    int ans = Sum(cellHigh, cellLow);
    int total = Sum(cellLow, ans);
    answerGrid[8].cellValue = total;
    
    cellHigh = answerGrid[14].cellValue;
    cellLow = answerGrid[8].cellValue;
    ans = Sum(cellHigh, cellLow);
    total = Sum(cellLow, ans);
    answerGrid[2].cellValue = total;
    */
    
    // loop instead

    for (int i = 0; i < 2; ++i)
    {
        int cellHigh = answerGrid[where -
                                  i * gridColumns]
                           .cellValue;
        int cellLow = answerGrid[where -
                                 (i + 1) * gridColumns]
                          .cellValue;

        int ans = Sum(cellHigh, cellLow);
        int total = Sum(cellLow, ans);
        answerGrid[where -
                   (i + 2) * gridColumns]
            .cellValue = total;
    }
}

void CGrid::InitDown(int where)
{
    for (int i = 0; i < 2; ++i)
    {
        int cellHigh = answerGrid[where +
                                  i * gridColumns]
                           .cellValue;
        int cellLow = answerGrid[where +
                                 (i + 1) * gridColumns]
                          .cellValue;

        int ans = Sum(cellHigh, cellLow);
        int total = Sum(cellLow, ans);
        answerGrid[where +
                   (i + 2) * gridColumns]
            .cellValue = total;
    }
}

void CGrid::InitLeft(int where)
{
    for (int i = 0; i < 2; ++i)
    {
        int cellHigh = answerGrid[where -
                                  i]
                           .cellValue;
        int cellLow = answerGrid[where -
                                 i - 1]
                          .cellValue;

        int ans = Sum(cellHigh, cellLow);
        int total = Sum(cellLow, ans);
        answerGrid[where -
                   i - 2]
            .cellValue = total;
    }
}

void CGrid::InitRight(int where)
{
    for (int i = 0; i < 2; ++i)
    {
        int cellHigh = answerGrid[where +
                                  i]
                           .cellValue;
        int cellLow = answerGrid[where +
                                 i + 1]
                          .cellValue;

        int ans = Sum(cellHigh, cellLow);
        int total = Sum(cellLow, ans);
        answerGrid[where + i + 2].cellValue = total;
    }
}

//void CGrid::InitialiseAnswer()
// we dont need to render the answers
// just keep them hidden
void CGrid::LoadAnswerGrid(SDL_Renderer *renderer)
{
    for (int i = 0; i < 36; ++i)
    {
        Cell temp{};
        answerGrid.push_back(temp);
    }
    // get visable w,x,y,z shown in game
    // into the answer
    answerGrid[20].cellValue =
        grid[20].cellValue;
    answerGrid[14].cellValue =
        grid[14].cellValue;
    answerGrid[21].cellValue =
        grid[21].cellValue;
    answerGrid[15].cellValue =
        grid[15].cellValue;
        
    // get the cross
    InitUp(middleNumbers::LEFT_DOWN);
    InitUp(middleNumbers::RIGHT_DOWN);
    InitDown(middleNumbers::LEFT_UP);
    InitDown(middleNumbers::RIGHT_UP);
    InitLeft(middleNumbers::RIGHT_UP);
    InitLeft(middleNumbers::RIGHT_DOWN);
    InitRight(middleNumbers::LEFT_UP);
    InitRight(middleNumbers::LEFT_DOWN);
    // fill the rest
    InitUp(middleNumbers::LEFT_THREE_DOWN);
    InitUp(middleNumbers::LEFT_TWO_DOWN);
    InitUp(middleNumbers::RIGHT_TWO_DOWN);
    InitUp(middleNumbers::RIGHT_THREE_DOWN);
    InitDown(middleNumbers::LEFT_THREE_UP);
    InitDown(middleNumbers::LEFT_TWO_UP);
    InitDown(middleNumbers::RIGHT_TWO_UP);
    InitDown(middleNumbers::RIGHT_THREE_UP);
    
    /*
    we dont want to see the answer
    
    for (int i = 0; i < answerGrid.size(); ++i)
    {
        std::string s =
            std::to_string(answerGrid[i].cellValue);
        answerGrid[i].cellValueTexture =
            loadText(renderer, s.c_str());
    }
    */
}

void CGame::HelpAnswerGrid()
{
    LoadAnswerGrid(renderer);
}

void CGrid::LoadGrid(SDL_Renderer *
                         renderer)
{
    // as the grid depends on the phone size
    
    for (int i = 0; i < 36; ++i)
    {
        Cell tempCell{};
        // temp alter for phone sizes
        // cells are square
        tempCell.w = cellWidth;
        tempCell.h = cellWidth;
        tempCell.cellValueRect.w = cellWidth -10;
        tempCell.cellValueRect.h = cellWidth - 10;
        
        // id
        tempCell.cellPos = i;
        tempCell.cellTexture = loadImage(
            renderer, "imgs/blankwhite.png");
        //test
        //std::string s = std::to_string(i);
        /*tempCell.cellValueTexture =
            loadText(renderer, s.c_str());
*/
        // deal with the positions in HandleUI
        grid.push_back(tempCell);

        // set numbers
        // possibly save game state?
        SetWXYZ();
        /*
        w = 2;
        x= 29;
        y = 9;
        z = 4;
        */
        
        switch (i)
        {
        case middleNumbers::LEFT_UP:
        {
            grid[i].cellValue = w;
            std::string sw = std::to_string(w);
            int size = sw.size();
            grid[i].cellValueLength = size;
            grid[i].cellValueTexture =
                loadText(renderer, sw.c_str());

            break;
        }
        case middleNumbers::RIGHT_UP:
        {
            grid[i].cellValue = x;
            std::string sx = std::to_string(x);
            int size = sx.size();
            grid[i].cellValueLength = size;
            grid[i].cellValueTexture =
                loadText(renderer, sx.c_str());
            /*
            grid[i].cellValueRect.x = xX;
            grid[i].cellValueRect.y = xY;
            */
            break;
        }
        case middleNumbers::LEFT_DOWN:
        {
            grid[i].cellValue = y;
            std::string sy = std::to_string(y);
            int size = sy.size();
            grid[i].cellValueLength = size;
            grid[i].cellValueTexture =
                loadText(renderer, sy.c_str());
            /*
            grid[i].cellValueRect.x = yX;
            grid[i].cellValueRect.y = yY;
            */
            break;
        }
        case middleNumbers::RIGHT_DOWN:
        {
            grid[i].cellValue = z;
            std::string sz = std::to_string(z);
            int size = sz.size();
            grid[i].cellValueLength = size;
            grid[i].cellValueTexture =
                loadText(renderer, sz.c_str());
            break;
        }
        default:
        {
            gridDebug = true;
            break;
        }
        }
    }

    selectTexture = loadImage(
        renderer,
        "imgs/blankblue.png");
}

// CGrid needs CGame renderer
void CGame::HelpGridLoad()
{
    LoadGrid(renderer);
}

void CKey::LoadKeys(
    SDL_Renderer *renderer,
    SDL_Rect rect,
    Keypad &keypad)
{
    files = {
        "keyONE.png",
        "keyTWO.png",
        "keyTHREE.png",
        "keyZERO.png",
        "keyMINUS.png",

        "keyFOUR.png",
        "keyFIVE.png",
        "keySIX.png",
        "keyAC.png",
        "keyPLUS.png",

        "keySEVEN.png",
        "keyEIGHT.png",
        "keyNINE.png",
        "keyBACK.png",
        "keyOK.png"};

    for (int i = 0; i < files.size(); ++i)
    {
        CKey key{};
        key.keyRect.w = keyWidth;
        key.keyRect.h = keyWidth;
        key.keypos = i;

        std::string s = "imgs/";
        s += files[i];

        key.keyTexture =
            loadImage(renderer, s.c_str());

        keypad.keys.push_back(key);
    }
    std::string h = "imgs/keyhighlight.png";

    keypad.keyHighlight =
        loadImage(renderer, h.c_str());

    // and some initialising a difficult keypad
    keypad.keys[0].value = 1;
    keypad.keys[0].kind = '8';
    keypad.keys[1].value = 2;
    keypad.keys[1].kind = '8';
    keypad.keys[2].value = 3;
    keypad.keys[2].kind = '8';
    keypad.keys[3].value = 0;
    keypad.keys[3].kind = '8';
    keypad.keys[4].value = -1;
    keypad.keys[4].kind = '-';
    keypad.keys[5].value = 4;
    keypad.keys[5].kind = '8';
    keypad.keys[6].value = 5;
    keypad.keys[6].kind = '8';
    keypad.keys[7].value = 6;
    keypad.keys[7].kind = '8';
    keypad.keys[8].value = -1;
    keypad.keys[8].kind = 'c';
    keypad.keys[9].value = -1;
    keypad.keys[9].kind = '+';
    keypad.keys[10].value = 7;
    keypad.keys[10].kind = '8';
    keypad.keys[11].value = 8;
    keypad.keys[11].kind = '8';
    keypad.keys[12].value = 9;
    keypad.keys[12].kind = '8';
    keypad.keys[13].value = -1;
    keypad.keys[13].kind = 'b';
    keypad.keys[14].value = -1;
    keypad.keys[14].kind = 'o';

    // extra hidden key
    CKey empty{};
    keypad.keys.push_back(empty);
    keypad.keys[15].kind = '*';
    keypad.keys[15].value = -1;
}

void CGame::HelpKeypadLoad(
    SDL_Renderer *renderer,
    SDL_Rect rect,
    Keypad &keypad)
{
    LoadKeys(renderer, rect, keypad);
}

void CGrid::SetWXYZ()
{
    int high = 30;
    w = (rand() % high);
    x = rand() % high;
    y = rand() % high;
    z = rand() % high;
}

int CGrid::CheckGrid()
{
    for(int i=0;i<grid.size();++i)
    {
        if(grid[i].cellValue == answerGrid[i].cellValue)
        {
            grid[i].cellMatch = true;
        }
        else
        {
            return i;
        }
    }
}

void CGrid::PutGrid(
    SDL_Renderer *renderer,
    const Display display)
{
    if (grid[selected].cellValueTexture == NULL)
    {
        grid[selected].cellValueTexture =
            loadText(renderer, display.myText);
    }
    else
    {
        // why didnt texture = NULL not work?
        // the cell should have emptied
        SDL_DestroyTexture(
            grid[selected].cellValueTexture);
        grid[selected].cellValueTexture =
            loadText(renderer, display.myText);
    }

    // cell associated with display
    grid[selected].cellValue =
        display.myTextToInt;
    grid[selected].cellValueLength =
        display.lengthOfDisplay;
        
    //test
    CheckGrid();
}

// our answer is a fairly important decision
void CGame::HelpPutGrid()
{
    PutGrid(renderer, display);
}

// match the grid coordinates
// grid left 0,0 - touch 0,0
// grid top 0,0 - touch 0,0
// grid right sw-grid size,0 - touch sw-720,0
void CGrid::SelectedCell(
    SDL_Rect touch, SDL_Rect grid)
{
    // i think grid.x is actually the w,x,y,z values
    /*
    int cellX = int((touch.x - grid.x) / CELLWIDTH);
    int cellY = int((touch.y - grid.y) / CELLWIDTH);
    */
    
    // plus gridArea.x as layouts 0 and 2
    // will be at 0,0
    // layout 1 will be at 820,0
    int cellX = int((touch.x - gridArea.x) / cellWidth);
    int cellY = int(touch.y /cellWidth);
    
    int valid = (gridColumns * cellY) + cellX;
    switch (valid)
    {
    case 14:
    case 15:
    case 20:
    case 21:
    {
        // disallowed
        break;
    }
    default:
    {
        selected = (gridColumns * cellY) + cellX;
    }
    }
}

// use touch Rect to select individual cells
void CGame::TouchingGrid()
{
    SelectedCell(touch, gridArea);
}

//void CGame::PositionCells(int offset)
void CGame::PositionGrid(int offset)
{
    for (int i = 0; i < grid.size(); ++i)
    {
        //grid[i].x += gridArea + ( ) ???
        
        // offset because in portrait or landscape
        // only x changes
        grid[i].x = (i % 6) * cellWidth + offset;
        grid[i].y = int(i / 6) * cellWidth;

        //the cellValues as well
        // in LoadGrid we shrink there w,h
        grid[i].cellValueRect.x = grid[i].x+5;
        grid[i].cellValueRect.y = grid[i].y+5;
    }
}

// a helpful post-input method
// handles texture creation and
// correct output
void CGame::HelpDisplayDisplay()
{
    // remove 0001 leading zeros
    try
    {
        display.myTextToInt =
            std::stoi(display.myText);
        std::string s =
            std::to_string(display.myTextToInt);

        strcpy(display.myText, s.c_str());
        display.lengthOfDisplay = s.length();
        gameDebug = false;
    }
    catch (std::invalid_argument &err)
    {
        strcpy(display.myText, "0");
        // stop 0 being stretched
        std::string ss = display.myText;
        display.lengthOfDisplay = ss.size();

        gameDebug = true;
    }

    // remove old text
    if (display.displayTexture != NULL)
    {
        SDL_DestroyTexture(display.displayTexture);
        display.displayTexture = NULL;
    }
    if (display.displayTexture == NULL)
    {
        display.displayTexture =
            loadText(renderer, display.myText);
    }
}

void CKey::GrabKeySize(int sw)
{
    keyWidth = int(sw / 6);
}

void CGrid::GrabGridSize(int sw)
{
    cellWidth = int(sw / gridColumns);
    valueWidth = cellWidth - 10;
}

void CGame::SendSize()
{
    GrabGridSize(screenWidth);
    GrabKeySize(screenWidth);
}

// every time SDL_FINGERDOWN
// we touch a key
// and call HelpDisplayDisplay
void CGame::TouchingKey(int i)
{
    // position for highlight
    int keypos = i;
    keypad.keyPressed = keypos;

    // please find the key we are on about
    CKey k = keypad.keys[i];
    switch (k.kind)
    {
    case '8':
    {
        // allow no more numbers
        if (display.lengthOfDisplay >=
            display.MAXINPUT)
        {
            return;
        }
        std::string s = std::to_string(k.value);
        strcat(display.myText, s.c_str());
        break;
    }
    case 'c':
    {
        strcpy(display.myText, "0");
        break;
    }
    case '-':
    {
        int i = std::stoi(display.myText);
        // only once
        if (i > 0)
        {
            i = 0 - i;
            std::string s = std::to_string(i);
            strcpy(display.myText, s.c_str());
            ++display.lengthOfDisplay;
        }
        break;
    }
    case '+':
    {
        int i = std::stoi(display.myText);
        // only once
        if (i < 0)
        {
            i = abs(i);
            std::string s = std::to_string(i);
            strcpy(display.myText, s.c_str());
            // length would be 1 less
            // as we remove the '-' symbol
            --display.lengthOfDisplay;
        }
        break;
    }
    case 'b':
    {
        std::string s = display.myText;
        s.pop_back();
        strcpy(display.myText, s.c_str());
        break;
    }
    // case 'o' will always be true
    // as keyPressed is always 14
    // unless there is a 15th key
    // to hide it
    case 'o':
    {
        HelpPutGrid();
        strcpy(display.myText, "0");
        break;
    }
    default:
    {
        // nothing yet
        gameDebug = true;
        strcpy(display.myText, "101");
        return;
        break;
    }
    }
}

// a rects x is always along the usual x axis
// and matches the screen width and height

/*
void CGame::HandleUI()
{
    // the left over screen space not grid
    int squareXSpace{screenWidth - 720};
    int squareYSpace{0};
    // nicely place the grid
    int gridXpos{0};
    int buffer{60};
    // better looking alignment
    const int keyRatio = int(720 / 6);
    const int keyHalf = int(720 / 12);

    switch (GetOrientation())
    {
    case 0:
    {
        squareXSpace = keyHalf;
        squareYSpace = screenHeight - 720 - keyRatio;
        break;
    }
    case 1:
    {
        gridXpos = screenWidth - 720 - buffer;
        squareXSpace = keyHalf;
        break;
    }
    case 2:
    {
        gridXpos += buffer;
        squareXSpace = screenWidth - 720;
        break;
    }
    // something went wrong
    default:
    {
        gameDebug = true;
        gridXpos = -360;
        squareXSpace = -360;
        squareYSpace = -360;
        break;
    }
    }

    gridArea.x = gridXpos;
    gridArea.y = 0;
    gridArea.w = 720;
    gridArea.h = 720;

    // move cells along with total grid area
    PositionGrid(gridXpos);

    display.numberDisplayRect.x =
        squareXSpace + keyRatio;
    display.numberDisplayRect.y =
        squareYSpace + keyRatio;
    display.numberDisplayRect.w =
        display.TEXTWIDTH * 6;
    display.numberDisplayRect.h = 100;

    // another go at display alignment
    // i need length of myText
    // to place in the middle
    display.numberDisplayRect.x =
        (screenWidth / 2) -
        (display.lengthOfDisplay * (display.TEXTWIDTH / 2));

    display.numberDisplayRect.w =
        display.TEXTWIDTH * display.lengthOfDisplay;

    keypad.fullKeypadRect.x =
        squareXSpace;
    keypad.fullKeypadRect.y =
        squareYSpace + keyRatio * 2;
    keypad.fullKeypadRect.w = 600;
    keypad.fullKeypadRect.h = 360;

    // place keys on keypad
    for (int i = 0; i < files.size(); ++i)
    {
        int whatX = int(i % 5) * KEYWIDTH;
        keypad.keys[i].keyRect.x =
            keypad.fullKeypadRect.x +
            whatX;
        int whatY = int(i / 5) * KEYWIDTH;
        keypad.keys[i].keyRect.y =
            keypad.fullKeypadRect.y +
            whatY;
    }
}
*/

// grab the screen info
// then we can lay components
// if phone rotated
void CGame::HandleUI()
{
    int layout = GetOrientationAndSize();
    
    // the left over screen space not grid
    int startXtraSpace{0};
    int endXtraSpace{0};
    int startYtraSpace{0};
    int endYtraSpace{0};
    
    // nicely place the grid
    int gridXpos{0};
    int buffer{60};
    // better looking alignment
    const int keyRatio = int(720 / 6);
    const int keyHalf = int(720 / 12);

    switch (layout)
    {
    case 0:
    {
        startYtraSpace = gridColumns * cellWidth;
        endYtraSpace = screenHeight;
        
        startXtraSpace = 0;
        endXtraSpace = screenWidth;
        
        gridXpos = 0;
        break;
    }
    case 1:
    {
        gridXpos = screenWidth - gridColumns * cellWidth - buffer;
        
        startXtraSpace = 0;
        endXtraSpace = screenWidth - gridColumns * cellWidth - buffer;
        
        startYtraSpace = 0;
        endYtraSpace = screenHeight;
        break;
    }
    case 2:
    {
        //gridXpos += buffer;
        gridXpos = 0 + buffer;
        
        startXtraSpace = gridColumns * cellWidth + buffer;
        endXtraSpace = screenWidth;
        
        startYtraSpace = 0;
        endYtraSpace = screenHeight;
        break;
    }
    // something went wrong
    default:
    {
        gameDebug = true;
        gridXpos = -360;
        break;
    }
    }

    gridArea.x = gridXpos;
    gridArea.y = 0;
    gridArea.w = gridColumns * cellWidth;
    gridArea.h = gridColumns * cellWidth;

    // move cells along with total grid area
    PositionGrid(gridXpos);

    //
    // display
    //
    /*
    display.numberDisplayRect.x =
        squareXSpace + keyRatio;
    display.numberDisplayRect.y =
        squareYSpace + keyRatio;
    display.numberDisplayRect.w =
        display.TEXTWIDTH * 6;
    display.numberDisplayRect.h = 100;
    */
    
    //
    // display
    //
    //========== border =======
    display.displayBorder.x =
        (endXtraSpace+startXtraSpace) / 2 -
            (display.TEXTWIDTH * 
                display.MAXDIGITS) / 2;
                
    display.displayBorder.y = startYtraSpace + buffer;
    //=============

    display.numberDisplayRect.x =
        display.displayBorder.x +
            display.displayBorder.w / 2 -
            (display.lengthOfDisplay *
                (display.TEXTWIDTH / 2));
    
    display.numberDisplayRect.y =
        display.displayBorder.y;

    display.numberDisplayRect.w =
        display.TEXTWIDTH * display.lengthOfDisplay;
        
    display.numberDisplayRect.h = 100;
        
    //
    // colourful indicators
    //
    
    
    //
    // keys
    //
    keypad.fullKeypadRect.x =
        startXtraSpace;
    keypad.fullKeypadRect.y =
        startYtraSpace + keyRatio * 2;
        /*
    keypad.fullKeypadRect.w = 600;
    keypad.fullKeypadRect.h = 360;
    */
    
    // temp values
    // keys[0] will be same as all keys
    Uint8 keyColumns = 5;
    Uint8 keyRows = 3;
    
    keypad.fullKeypadRect.w =
        keypad.keys[0].keyRect.w * keyColumns;
    keypad.fullKeypadRect.h =
        keypad.keys[0].keyRect.h * keyRows;

    // place keys on keypad
    for (int i = 0; i < files.size(); ++i)
    {
        int whatX = int(i % 5) * keyWidth;
        keypad.keys[i].keyRect.x =
            keypad.fullKeypadRect.x +
            whatX;
        int whatY = int(i / 5) * keyWidth;
        keypad.keys[i].keyRect.y =
            keypad.fullKeypadRect.y +
            whatY;
    }
}

// return what phone rotation is
int CGame::GetOrientationAndSize()
{
    int ans{0};
    // we can adjust keypad bottom,
    // right or left
    switch (SDL_GetDisplayOrientation(0))
    {
    case SDL_ORIENTATION_PORTRAIT:
    case SDL_ORIENTATION_PORTRAIT_FLIPPED:
    {
        ans = 0;
        break;
    }
    case SDL_ORIENTATION_LANDSCAPE:
    {
        ans = 1;
        break;
    }
    case SDL_ORIENTATION_LANDSCAPE_FLIPPED:
    {
        ans = 2;
        break;
    }
    case SDL_ORIENTATION_UNKNOWN:
    {
        ans = 3;
        break;
    }
    default:
    {
        gameDebug = true;
    }
    }

    SDL_GetRendererOutputSize(
        renderer,
        &screenWidth,
        &screenHeight);

    return ans;
}

// on an event we can update the screen
// it's not necessary to update every frame?'
void CGame::InputGame()
{
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_FINGERDOWN:
        {
            f = event.tfinger;

            touch.x = f.x * screenWidth;
            touch.y = f.y * screenHeight;

            if (SDL_HasIntersection(
                    &touch, &gridArea))
            {
                TouchingGrid();
            }

            // if we aren't pressing anything
            keypad.keyPressed =
                namedKey::KEY_EMPTY;

            if (SDL_HasIntersection(
                    &touch, &keypad.fullKeypadRect))
            {
                for (int i = 0; i < files.size(); ++i)
                {
                    if (SDL_HasIntersection(
                            &touch,
                            &keypad.keys[i].keyRect))
                    {
                        TouchingKey(i);
                    }
                }

                //we place it by hitting OK
                /*
                DO THIS IN TOUCHING KEY
                
                if (SDL_HasIntersection(
                        &touch,
                        &keypad.keys
                        [namedKey::KEY_OK].keyRect))
                {
                */
            }
            // here is the per touch update
            HelpDisplayDisplay();
            break;
        }
        case SDL_FINGERUP:
        {
            keypad.keyPressed =
                namedKey::KEY_EMPTY;
        }
        case SDL_FINGERMOTION:
        {
            // cancel things
            keypad.keyPressed =
                namedKey::KEY_EMPTY;
            break;
        }
        default:
        {
            gameDebug = true;
        }
        }
    }
}

void CGame::UpdateScreen()
{
    SDL_SetRenderDrawColor(
        renderer,
        0, 0, 0, 255);

    SDL_RenderClear(renderer);
    /*SDL_SetRenderDrawBlendMode(
        renderer, SDL_BLENDMODE_BLEND);
*/
    //
    // grid cells
    //
    for (int i = 0; i < grid.size(); ++i)
    {
        // convert Cell to Rect
        SDL_Rect temp{};
        temp.x = grid[i].x;
        temp.y = grid[i].y;
        temp.w = grid[i].w;
        temp.h = grid[i].h;

        SDL_RenderCopy(
            renderer,
            grid[i].cellTexture,
            NULL,
            &temp);

        // if a cell is selected
        if (i == selected)
        {
            SDL_RenderCopy(
                renderer,
                selectTexture,
                NULL,
                &temp);
        }
        //
        // match answer
        //
        if(grid[i].cellMatch)
        {
            SDL_SetRenderDrawColor(
                renderer, 0, 200, 10, 255);
        }
        else
        {
            SDL_SetRenderDrawColor(
                renderer, 200, 10, 0, 255);
        }
        SDL_RenderFillRect(
            renderer, &grid[i].cellValueRect);
        //
        // cellValueTexture
        //
        if (grid[i].cellValueTexture != NULL)
        {
            SDL_RenderCopy(
                renderer,
                grid[i].cellValueTexture,
                NULL,
                &grid[i].cellValueRect);
        }
        
        // testing ans
        /*
        if (answerGrid[i].cellValueTexture != NULL)
        {
            SDL_RenderCopy(
                renderer,
                answerGrid[i].cellValueTexture,
                NULL,
                &grid[i].cellValueRect);
        }
        */
    }
    
    //
    // display
    //
    //
    // ===== border ========
    SDL_SetRenderDrawColor(renderer,
                           200, 200, 250, 255);
    SDL_RenderDrawRect(renderer,
                       &display.displayBorder);
    //=========================

    if (display.displayTexture != NULL)
    {
        SDL_RenderCopy(
            renderer,
            display.displayTexture,
            NULL,
            &display.numberDisplayRect);
    }
    else
    {
        gameDebug = true;
    }

    //
    // keypad
    //
    // test we cover up the blue test area
    SDL_SetRenderDrawColor(renderer,
                           50, 150, 50, 255);
    SDL_RenderFillRect(renderer,
                       &keypad.fullKeypadRect);

    SDL_RenderCopy(
        renderer,
        keypad.keyHighlight,
        NULL,
        &keypad.keys[keypad.keyPressed].keyRect);

    for (int i = 0; i < files.size(); ++i)
    {
        //if(!=NULL)
        SDL_RenderCopy(
            renderer,
            keypad.keys[i].keyTexture,
            NULL,
            &keypad.keys[i].keyRect);
    }

    //
    // debug
    //
    if (gameDebug || gridDebug || keyDebug)
    {
        SDL_Rect d{0, screenHeight / 2, screenWidth, 30};

        SDL_SetRenderDrawColor(
            renderer,
            255, 255, 0, 255);

        SDL_RenderFillRect(
            renderer, &d);
    }

    SDL_RenderPresent(renderer);
}