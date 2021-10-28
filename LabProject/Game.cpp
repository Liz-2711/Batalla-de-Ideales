#include "Game.h"
#include"SDL_image.h"

SDL_Texture* playText;
SDL_Rect scrR, destR;
SDL_Rect    rcSprite;
SDL_Rect    gdSprite;

int gameover = 0;
Game::Game()
{}

Game::~Game()
{}

const int SPRITE_SIZE = 256;

void Game::init(const char* title, int WIDTH, int HEIGHT, bool fullscreen)
{




    
        SDL_Init(SDL_INIT_EVERYTHING);
        SDL_Surface* imageSurface = NULL;
        SDL_Surface* windowSurface = NULL;
        SDL_Surface* temp = NULL;
        SDL_Surface* sprite = NULL;
        SDL_Surface* SDL_DisplayFormat(SDL_Surface * surface);
        SDL_Rect    rcSprite;
        SDL_Rect    gdSprite;
        SDL_Event windowEvent;
        SDL_Event   event;
        SDL_Renderer* renderer = NULL;
        SDL_Texture* texture;
        SDL_Texture* spriteTexture;

        const Uint8* keystate;
        int colorkey;
        int count;
        int xPosition = 0;
        int yPosition = 0;
        int gameover = 0;


        SDL_Window* window = SDL_CreateWindow("Intro", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
        windowSurface = SDL_GetWindowSurface(window);

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);



        //imageSurface = IMG_Load("IntroBK.png");
        sprite = IMG_Load("IntroBK.png");

        int SPRITE_SIZE = 1;
        //int SPRITE_SIZE = sprite->h * sprite->w;
        texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
        spriteTexture = SDL_CreateTextureFromSurface(renderer, sprite);

        SDL_FreeSurface(sprite);
        SDL_FreeSurface(imageSurface);

        //rcSprite used as source rectangle, gdSprite as destination rectangle. Initialize them to the same position
        rcSprite.x = 0;
        rcSprite.y = 0;
        rcSprite.w = 800;
        rcSprite.h = 600;

        gdSprite.x = xPosition;
        gdSprite.y = yPosition;
        gdSprite.w = 800;
        gdSprite.h = 800;

        while (!gameover)
        {
            if (SDL_PollEvent(&event))
            {
                switch (event.type)
                {
                case SDL_QUIT:
                    gameover = 1;
                    break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                    case SDLK_q:
                        gameover = 1;
                        break;

                    }
                    break;
                }
            }

            keystate = SDL_GetKeyboardState(NULL);

            // When key pressed, update the destination rectangle

            if (keystate[SDL_SCANCODE_UP]) {
               // gdSprite.y -= 1;              
                rcSprite.y += 2;
            }
            if (keystate[SDL_SCANCODE_DOWN]) {
             //   gdSprite.y += 1;
                rcSprite.y -= 2;
            }
            if (gdSprite.x < 0) {
                gdSprite.x = 0;
            }
          //  else if (gdSprite.x > WIDTH - SPRITE_SIZE) {
             //   gdSprite.x = WIDTH - SPRITE_SIZE;
           // }
            /* if (gdSprite.y < 0) {
                 gdSprite.y = 0;
             }
             else if (gdSprite.y > HEIGHT - SPRITE_SIZE) {
                 gdSprite.y = HEIGHT - SPRITE_SIZE;
             }*/

             //Render the window
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, &gdSprite);
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderCopy(renderer, spriteTexture, &rcSprite, &gdSprite);
            SDL_RenderPresent(renderer);



        }


        SDL_DestroyTexture(spriteTexture);
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);




        SDL_Quit();
        
    
    }
	/*SDL_Event event;
	SDL_Renderer* renderer = NULL;
	SDL_Texture* texture = NULL;
	SDL_Window* window = NULL;

	SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(
		800, 500,
		0, &window, &renderer
	);
	IMG_Init(IMG_INIT_PNG);
	texture = IMG_LoadTexture(renderer, "DarkBK.png");
	while (1) {
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
		if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
			break;
	}

	SDL_DestroyTexture(texture);
	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
*/

/*****************************************************************************************************************************************************
    SDL_Surface* imageSurface = NULL;
    SDL_Surface* windowSurface = NULL;
    SDL_Surface* temp = NULL;
    SDL_Surface* sprite = NULL;
    SDL_Surface* SDL_DisplayFormat(SDL_Surface * surface);
    SDL_Rect    rcSprite;
    SDL_Rect    gdSprite;
    SDL_Event windowEvent;
    SDL_Event   event;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* texture;
    SDL_Texture* spriteTexture;

    const Uint8* keystate;
    int colorkey;
    int count;
    int xPosition = 0;
    int yPosition = 0;
    int gameover = 0;


    SDL_Window* window = SDL_CreateWindow("ABDUCTO", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_ALLOW_HIGHDPI);
    windowSurface = SDL_GetWindowSurface(window);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    imageSurface = IMG_Load("farm.png");
    sprite = IMG_Load("DarkBK.png");

    texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    spriteTexture = SDL_CreateTextureFromSurface(renderer, sprite);

    SDL_FreeSurface(sprite);
    SDL_FreeSurface(imageSurface);

    //rcSprite used as source rectangle, gdSprite as destination rectangle. Initialize them to the same position
    rcSprite.x = xPosition;
    rcSprite.y = yPosition;
    rcSprite.w = SPRITE_SIZE;
    rcSprite.h = SPRITE_SIZE;

    gdSprite.x = xPosition;
    gdSprite.y = yPosition;
    gdSprite.w = SPRITE_SIZE;
    gdSprite.h = SPRITE_SIZE;

    while (!gameover)
    {
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                gameover = 1;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                case SDLK_q:
                    gameover = 1;
                    break;

                }
                break;
            }
        }

        keystate = SDL_GetKeyboardState(NULL);

        // When key pressed, update the destination rectangle
        if (keystate[SDL_SCANCODE_LEFT]) {
            gdSprite.x -= 2;
        }
        if (keystate[SDL_SCANCODE_RIGHT]) {
            gdSprite.x += 2;
        }
        if (keystate[SDL_SCANCODE_UP]) {
            gdSprite.y -= 2;
        }
        if (keystate[SDL_SCANCODE_DOWN]) {
            gdSprite.y += 2;
        }
        if (gdSprite.x < 0) {
            gdSprite.x = 0;
        }
        else if (gdSprite.x > width - SPRITE_SIZE) {
            gdSprite.x = width - SPRITE_SIZE;
        }
        if (gdSprite.y < 0) {
            gdSprite.y = 0;
        }
        else if (gdSprite.y > height - SPRITE_SIZE) {
            gdSprite.y = height - SPRITE_SIZE;
        }

        //Render the window
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderCopy(renderer, spriteTexture, &rcSprite, &gdSprite);
        SDL_RenderPresent(renderer);

        //SDL_BlitSurface(imageSurface, NULL, windowSurface, NULL);
        //SDL_BlitSurface(sprite, NULL, imageSurface, &rcSprite);
        //SDL_UpdateWindowSurface(window);


        //update the source rectangle to move with the sprite??
        rcSprite.x = gdSprite.x;
        rcSprite.y = gdSprite.y;

    }


    SDL_DestroyTexture(spriteTexture);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);


   

    SDL_Quit();

    */
        //**************************************************************************************************************************

/*	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}

	SDL_Surface* tempSurface = IMG_Load("DarkBK.png");
	
	playText = SDL_CreateTextureFromSurface(renderer, tempSurface);

	
	SDL_FreeSurface(tempSurface);

    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Surface* imageSurface = NULL;
    SDL_Surface* windowSurface = NULL;
    SDL_Surface* temp = NULL;
    SDL_Surface* sprite = NULL;
    SDL_Surface* SDL_DisplayFormat(SDL_Surface * surface);
    SDL_Rect    rcSprite;
    SDL_Rect    gdSprite;
    SDL_Event windowEvent;
    SDL_Event   event;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* texture;
    SDL_Texture* spriteTexture;

    const Uint8* keystate;
    int colorkey;
    int count;
    int xPosition = 400;
    int yPosition = 0;
    int gameover = 0;


    SDL_Window* window = SDL_CreateWindow("Intro", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    windowSurface = SDL_GetWindowSurface(window);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    //imageSurface = IMG_Load("IntroBK.png");
    sprite = IMG_Load("IntroBK.png");

    texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    spriteTexture = SDL_CreateTextureFromSurface(renderer, sprite);

    SDL_FreeSurface(sprite);
    SDL_FreeSurface(imageSurface);

    //rcSprite used as source rectangle, gdSprite as destination rectangle. Initialize them to the same position
    rcSprite.x = 0;
    rcSprite.y = 0;
    rcSprite.w = SPRITE_SIZE;
    rcSprite.h = SPRITE_SIZE;

    gdSprite.x = xPosition;
    gdSprite.y = yPosition;
    gdSprite.w = SPRITE_SIZE;
    gdSprite.h = SPRITE_SIZE;

    while (!gameover)
    {
        if (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                gameover = 1;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                case SDLK_q:
                    gameover = 1;
                    break;

                }
                break;
            }
        }

        keystate = SDL_GetKeyboardState(NULL);

        // When key pressed, update the destination rectangle

        if (keystate[SDL_SCANCODE_UP]) {
            gdSprite.y -= 1;
        }
        if (keystate[SDL_SCANCODE_DOWN]) {
            gdSprite.y += 1;
        }
        if (gdSprite.x < 0) {
            gdSprite.x = 0;
        }
        else if (gdSprite.x > WIDTH - SPRITE_SIZE) {
            gdSprite.x = WIDTH - SPRITE_SIZE;
        }
        if (gdSprite.y < 0) {
            gdSprite.y = 0;
        }
        else if (gdSprite.y > HEIGHT - SPRITE_SIZE) {
            gdSprite.y = HEIGHT - SPRITE_SIZE;
        }

        //Render the window
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, &gdSprite);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderCopy(renderer, spriteTexture, &rcSprite, &gdSprite);
        SDL_RenderPresent(renderer);



    }


    SDL_DestroyTexture(spriteTexture);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);




    SDL_Quit();
    return 0;*/


void Game::handleEvents()
{
	SDL_Event event;

	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}



void Game::update()
{
	destR.y = 500;
	cnt--;
	destR.h = 600;
	destR.w = 800;
	//destR.x = 40;


	//moving 
	
	//destR.y = cnt;


	std::cout << cnt << std::endl;
}

void Game::render()
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, playText,NULL,&destR);
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}