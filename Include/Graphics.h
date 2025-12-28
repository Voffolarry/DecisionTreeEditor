#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL3/SDL.h>
#include <string>

class Graphics {
    private:
      SDL_Window* window;     // Fenetre SDL
      SDL_Renderer* renderer; // Moteur de rendu
    public:
      Graphics();

      bool init(const std::string& title, int width, int height);
      void Clear();
      void Present();
      void Quit();
};
#endif