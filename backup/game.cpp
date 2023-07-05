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
    return 0;
}

void CGame::QuitGame()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
}

int CGame::Run()
{
    // load gfx
    HelpGridLoad(renderer);
    HelpKeypadLoad(
        renderer,
        keypad.fullKeypadRect,
        keypad);
    // get a zero up
    HelpDisplayDisplay();
        
    //HandleUI();
        
    while (loopgame)
    {
        HandleUI();
        InputGame();
        UpdateScreen();
    }

    QuitGame();
    return 0;
}

void CGrid::LoadGrid(SDL_Renderer *
                         renderer)
{
    for (int i = 0; i < 36; ++i)
    {
        Cell tempCell{};
        tempCell.cellTexture = loadImage(
            renderer, "imgs/blankwhite.png");
            
        // deal with the positions in HandleUI
        grid.push_back(tempCell);
    }

    selectTexture = loadImage(
        renderer,
        "imgs/blankred.png");
}

// CGrid needs CGame renderer
void CGame::HelpGridLoad(
    SDL_Renderer *renderer)
{
    LoadGrid(renderer);
}

void CKey::LoadKeys(
    SDL_Renderer *renderer,
    SDL_Rect rect,
    Keypad& keypad)
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
        key.keyRect.w = 120;
        key.keyRect.h = 120;
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
    keypad.keys[15].kind = 'o';
}

void CGame::HelpKeypadLoad(
    SDL_Renderer *renderer,
    SDL_Rect rect,
    Keypad& keypad)
{
    LoadKeys(renderer, rect, keypad);
}

// a helpful post-input method
// handles texture creation and
// correct output
void CGame::HelpDisplayDisplay()
{
    // remove 0001 leading zeros
    try
    {
        display.myTextInt =
             std::stoi(display.myText);
        std::string s =
            std::to_string(display.myTextInt);
        //lengthOfText = s.length();
        strcpy(display.myText, s.c_str());
        display.lengthOfDisplay = s.length();
    }
    catch (std::invalid_argument &err)
    {
        //strcpy(display.myText, "NAN");
        strcpy(display.myText, "0");
    }
    
    // remove old text
    if(display.displayTexture != NULL)
    {
        SDL_DestroyTexture(display.displayTexture);
        display.displayTexture = NULL;
    }
    if(display.displayTexture == NULL)
    {
    display.displayTexture =
        loadText(renderer, display.myText);
    }
}

// match the grid coordinates
// grid left 0,0 - touch 0,0
// grid top 0,0 - touch 0,0
// grid right sw-grid size,0 - touch sw-720,0
void CGrid::SelectedCell(
    SDL_Rect touch, SDL_Rect grid)
{
    int cellX = int((touch.x - grid.x) / 120);
    int cellY = int((touch.y - grid.y) / 120);
    selected = (6 * cellY) + cellX;
}

// use touch Rect to select individual cells
void CGame::TouchingGrid()
{
    SelectedCell(touch, gridArea);
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
    switch(k.kind)
    {
        case '8':
        {
            std::string s = std::to_string(k.value);
            strcat(display.myText, s.c_str());
            
            //+display.lengthOfDisplay;
            break;
        }
        case 'c':
        {
            strcpy(display.myText, "0");
            
            //display.lengthOfDisplay = 0;
            break;
        }
        case '-':
        {
            int i = std::stoi(display.myText);
            i = 0-i;
            std::string s = std::to_string(i);
            strcpy(display.myText, s.c_str());
            break;
        }
        case '+':
        {
            int i = std::stoi(display.myText);
            i = abs(i);
            std::string s = std::to_string(i);
            strcpy(display.myText, s.c_str());
            break;
        }
        case 'b':
        {
            std::string s = display.myText;
            s.pop_back();
            strcpy(display.myText, s.c_str());
            break;
        }
    }
    //switch(kind)
    //case
}

// a rects x is always along the usual x axis
// and matches the screen width and height
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
        (screenWidth/2) -
            (display.lengthOfDisplay
            * (display.TEXTWIDTH /2));
                
    display.numberDisplayRect.w =
        display.TEXTWIDTH * display.lengthOfDisplay;

    keypad.fullKeypadRect.x =
        squareXSpace;
    keypad.fullKeypadRect.y =
        squareYSpace + keyRatio * 2;
    keypad.fullKeypadRect.w = 600;
    keypad.fullKeypadRect.h = 360;

    // when the keypad changes
    // position, update all keys
    for (int i = 0; i < files.size(); ++i)
    {
        int whatX = int(i % 5) * 120;
        keypad.keys[i].keyRect.x =
            keypad.fullKeypadRect.x +
                whatX;
        int whatY = int(i / 5) * 120;
        keypad.keys[i].keyRect.y =
            keypad.fullKeypadRect.y +
                whatY;
    }
}

void CGame::PositionGrid(int offset)
{
    for (int i = 0; i < grid.size(); ++i)
    {
        grid[i].x = (i % 6) * 120 + offset;
        grid[i].y = int(i / 6) * 120;
    }
}

// return what phone rotation is
int CGame::GetOrientation()
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
            keypad.keyPressed = 14;
            
            for(int i=0;i<files.size();++i)
            {
                if(SDL_HasIntersection(
                    &touch,
                    &keypad.keys[i].keyRect))
                {
                    TouchingKey(i);
                    //TouchingKey(CKey key.kind);
                }
            }
            // here is the per touch update
            HelpDisplayDisplay();
            break;
        }
        case SDL_FINGERUP:
        {
            keypad.keyPressed = 14;
        }
        case SDL_FINGERMOTION:
        {
            // cancel things
            /*
            there might be an error later
            if OK if pressed
            we will always send
            too early
            */
            keypad.keyPressed = 14;
            break;
        }
        }
        /*
        switch(event.display.event)
        {
            case SDL_DISPLAYEVENT_ORIENTATION:
            {
                HandleUI();
                break;
            }
        }
        */
    }
}

void CGame::UpdateScreen()
{
    SDL_SetRenderDrawColor(
        renderer,
        0, 0, 0, 255);

    SDL_RenderClear(renderer);

    //
    // grid
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
    }

    //
    // display
    //
    SDL_SetRenderDrawColor(renderer,
                           200, 200, 250, 255);
    SDL_RenderDrawRect(renderer,
        &display.numberDisplayRect);
    /*SDL_RenderFillRect(renderer,
                       &display.numberDisplayRect);
    */
    if(display.displayTexture != NULL)
    {
        SDL_RenderCopy(
            renderer,
            display.displayTexture,
            NULL,
            &display.numberDisplayRect);
    }
    //
    // keypad
    //
    SDL_SetRenderDrawColor(renderer,
                           50, 150, 50, 255);
    SDL_RenderFillRect(renderer,
                       &keypad.fullKeypadRect);
    /*
    SDL_Rect r{0,0,120,120};
    SDL_RenderCopy(
        renderer,
        debugText,
        NULL,
        &r);
    
    SDL_RenderCopy(
        renderer,
        keypad.keys[0].keyTexture,
        NULL,
        &keypad.keys[0].keyRect);
    */
    
    SDL_RenderCopy(
            renderer,
            keypad.keyHighlight,
            NULL,
            &keypad.keys[keypad.keyPressed].keyRect);
            
    for (int i = 0; i < files.size(); ++i)
    {
        /*
        i would need a spare index to hide it
        unless it went on OK
        */
        SDL_RenderCopy(
            renderer,
            keypad.keys[i].keyTexture,
            NULL,
            &keypad.keys[i].keyRect);
    }
    

    if (debug)
    {
        SDL_Rect d{0, 0, screenWidth, 100};

        SDL_SetRenderDrawColor(
            renderer,
            255, 255, 0, 255);
        /*
    if (screenWidth > 720)
    {
        SDL_SetRenderDrawColor(
            renderer,
            0, 255, 255, 255);
    }
    else
    {
        SDL_SetRenderDrawColor(
            renderer,
            255, 255, 0, 255);
    }
    */
        SDL_RenderFillRect(
            renderer, &d);
    }

    SDL_RenderPresent(renderer);
}