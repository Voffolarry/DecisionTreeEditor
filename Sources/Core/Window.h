#pragma once

#include <SDL3/SDL.h>
#include <string>
#include <iostream>

namespace Core {

    class Window {
    public:
        Window(const std::string& title, int width, int height);
        ~Window();

        bool Initialize();
        void PollEvents(bool& quit);
        void Clear(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
        void Present();
        
        SDL_Renderer* GetRenderer() const { return m_Renderer; }
        SDL_Window* GetNativeWindow() const { return m_Window; }

    private:
        std::string m_Title;
        int m_Width;
        int m_Height;
        SDL_Window* m_Window;
        SDL_Renderer* m_Renderer;
    };

}
