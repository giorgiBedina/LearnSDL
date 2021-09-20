#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

//The window we'll be rendering to
SDL_Window* gWindow = NULL;
    
//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* gShowPicture = NULL;

//Starts up SDL and creates window
bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow( "show image", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, true );
        if( gWindow == NULL )
        {
            std::cout << "Window could not be created! SDL_Error: \t" << SDL_GetError() << std::endl;
            success = false;
        }
        else
        {
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface( gWindow );
        }
    }

    return success;
}

//Loads media
bool loadMedia(){
    //Loading success flag
    bool success = true;

    //Load splash image
    gShowPicture = SDL_LoadBMP( "picture/picture.bmp" );
    if( gShowPicture == NULL )
    {
        std::cout << "Unable to load image ! SDL Error: \t" <<  "picture/picture.bmp \t" << SDL_GetError() << std::endl;
        success = false;
    }

    return success;
}

//Frees media and shuts down SDL
void close()
{
    //Deallocate surface
    SDL_FreeSurface( gShowPicture );
    gShowPicture = NULL;

    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}


int main()
{
 //Start up SDL and create window
    if( !init() )
    {
        std::cout << "Failed to initialize!" << std::endl;
    }
    else
    {
        //Load media
        if( !loadMedia() )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
            //Apply the image
            SDL_BlitSurface( gShowPicture, NULL, gScreenSurface, NULL );
            //Update the surface
            SDL_UpdateWindowSurface( gWindow );   
            //Wait two seconds
            SDL_Delay( 6000 );
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}
