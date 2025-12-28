#include "Graphics.h"

Graphics:Graphics(): window(nullptr), renderer(nullptr){}

/**
 * Initialisation (init)
 */
bool Graphics::init(const std::string& title, int width, int height){
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        return false;
    }

    window = SDL_CreateWindow(
        title.c_str(),
        width,
        height,
        0
    );

    renderer = SDL_CreateRenderer(window, nullptr, 0);

    return window && renderer;
}


/**
 * Nettoyage de l'ecran (clear)
 */

 void Graphics::Clear(){
    SDL_SetRendererDrawColor(renderer, 255, 255, 255, 255);
    SDL_RendererClear(renderer);
}

/**
 * Affichage a l'ecran (present)
 */

void Graphics::Present(){
    SDL_RendererPresent(renderer);
}

/**
 * Fermeture (quit)
 */

void Graphics::Quit(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}