#include "Window.h"

namespace Core {

    Window::Window(const std::string& title, int width, int height)
        : m_Title(title), m_Width(width), m_Height(height), m_Window(nullptr), m_Renderer(nullptr) {
    }

    Window::~Window() {
        if (m_Renderer) {
            SDL_DestroyRenderer(m_Renderer);
        }
        if (m_Window) {
            SDL_DestroyWindow(m_Window);
        }
        SDL_Quit();
    }

    bool Window::Initialize() {
        if (!SDL_Init(SDL_INIT_VIDEO)) {
            std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
            return false;
        }

        m_Window = SDL_CreateWindow(m_Title.c_str(), m_Width, m_Height, 0);
        if (!m_Window) {
            std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            return false;
        }

        m_Renderer = SDL_CreateRenderer(m_Window, NULL);
        if (!m_Renderer) {
            std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
            return false;
        }

        return true;
    }

    void Window::PollEvents(bool& quit) {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }
    }

    void Window::Clear(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        SDL_SetRenderDrawColor(m_Renderer, r, g, b, a);
        SDL_RenderClear(m_Renderer);
    }

    void Window::Present() {
        SDL_RenderPresent(m_Renderer);
    }

}
