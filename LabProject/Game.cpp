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


//*****************************************************************************************************************************************************************************
        SDL_AudioSpec wavSpec;
        Uint32 wavLength;
        Uint8* wavBuffer;

        SDL_LoadWAV("IntroUT.wav", &wavSpec, &wavBuffer, &wavLength);

        SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);

        int success = SDL_QueueAudio(deviceId, wavBuffer, wavLength);
        SDL_PauseAudioDevice(deviceId, 0);


        // keep application running long enough to hear the sound

        SDL_Delay(3000);
       //************************************************************************************************************************************************

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
                rcSprite.y += 1;
            }
            if (keystate[SDL_SCANCODE_DOWN]) {
             //   gdSprite.y += 1;
                rcSprite.y -= 1;
            }
            if (gdSprite.x < 0) {
                gdSprite.x = 0;
            }
          

             //Render the window
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, texture, NULL, &gdSprite);
            SDL_RenderCopy(renderer, texture, NULL, NULL);
            SDL_RenderCopy(renderer, spriteTexture, &rcSprite, &gdSprite);
            SDL_RenderPresent(renderer);



        }
      

        // clean up

        SDL_CloseAudioDevice(deviceId);
        SDL_FreeWAV(wavBuffer);
        

        SDL_DestroyTexture(spriteTexture);
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);




        SDL_Quit();
        
    
    }

   


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
    SDL_CloseAudio();
    

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}