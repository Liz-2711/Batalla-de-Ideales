#include<SDL.h>

#include"SDL_image.h"
#include "Game.h"







    Game* game = nullptr;

    int main(int argc, char* argv[])
    {

        const int FPS = 60;
        const int frameDelay = 100 / FPS;

        Uint32 frameStart;
        int frmeTime;

        game = new Game();
        game->init("GameWindow", 800, 600, false);

        while (game->running())
        {

            frameStart = SDL_GetTicks();
            game->handleEvents();
            game->update();
            game->render();
        }

        game->clean();
        return 0;











   /* SDL_Init(SDL_INIT_EVERYTHING);
    //For loading PNG images
    IMG_Init(IMG_INIT_PNG);
    SDL_Window* window = SDL_CreateWindow("Getting Started", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_Event input;
    bool quit = false;

    SDL_Texture* texture = NULL;
    SDL_Surface* temp = IMG_Load("DarkBK.png");

    //Filling texture with the image using a surface
    texture = SDL_CreateTextureFromSurface(renderer, temp);
    
    //Deleting the temporary surface
    SDL_FreeSurface(temp);

    SDL_Rect rect;
    rect.x = 0; //Extreme left of the window
    rect.y = 0; //Very bottom of the window
    rect.w = 800; //100 pixels width
    rect.h = 600; //100 pixels height
    //'rect' defines the dimensions for the bottom-left of the window

    while (!quit)
    {
        while (SDL_PollEvent(&input) > 0)
        {
            if (input.type == SDL_QUIT) quit = true;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //Copying the texture on to the window using renderer and rectangle
        SDL_RenderCopy(renderer, texture, NULL, &rect);

        SDL_RenderPresent(renderer);
    }
    */
  /**************************************************************************************************************************/
   /* const SDL_MessageBoxButtonData buttons[] = {
        { // .flags, .buttonid, .text 
            0, 0, "no" },
        { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "yes" },
        { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "cancel" },
    };
    const SDL_MessageBoxColorScheme colorScheme = {
        { // .colors (.r, .g, .b) *
            // [SDL_MESSAGEBOX_COLOR_BACKGROUND
            { 255,   0,   0 },
            //[SDL_MESSAGEBOX_COLOR_TEXT] *
            {   0, 255,   0 },
            // [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] *
            { 255, 255,   0 },
            // [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] *
            {   0,   0, 255 },
            // [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] *
            { 255,   0, 255 }
        }
    };
    const SDL_MessageBoxData messageboxdata = {
        SDL_MESSAGEBOX_INFORMATION, // .flags *
        NULL, // .window *
        "example message box", // .title 
        "select a button", // .message *
        SDL_arraysize(buttons), // .numbuttons /
        buttons, // .buttons /
        &colorScheme // .colorScheme /
    };
    int buttonid;
    if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
        SDL_Log("error displaying message box");
        return 1;
    }
    if (buttonid == -1) {
        SDL_Log("no selection");
    }
    else {
        SDL_Log("selection was %s", buttons[buttonid].text);
    }
    system("PAUSE");
    */

    /**************************************************************************************************************************/

    //Deleting the texture
 /*   SDL_DestroyTexture(texture);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    //For quitting IMG systems
    IMG_Quit();

    SDL_Quit();

    return 0;*/
    }
		