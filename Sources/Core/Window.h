/**
 * Window.h
 * SDL3 window and renderer wrapper
 * 
 * Provides a high-level interface for creating and managing an SDL3 window
 * and its associated renderer. Handles initialization, event polling, and rendering.
 */

#pragma once

#include <SDL3/SDL.h>
#include <string>
#include <iostream>

namespace Core {

    /**
     * @class Window
     * @brief Wrapper class for SDL3 window and renderer management
     * 
     * Encapsulates SDL3 window creation, initialization, and basic rendering operations.
     * Manages the lifecycle of both the window and renderer, ensuring proper cleanup.
     */
    class Window {
    public:
        /**
         * @brief Construct a Window with specified parameters
         * @param title Window title displayed in title bar
         * @param width Window width in pixels
         * @param height Window height in pixels
         */
        Window(const std::string& title, int width, int height);
        
        /**
         * @brief Destructor - cleans up SDL resources
         * 
         * Destroys the renderer, window, and quits SDL.
         */
        ~Window();

        /**
         * @brief Initialize SDL and create the window and renderer
         * @return true if initialization succeeded, false on error
         * 
         * Must be called after construction before using the window.
         * Errors are logged to stderr.
         */
        bool Initialize();
        
        /**
         * @brief Poll SDL events and update quit flag
         * @param quit Reference to boolean flag, set to true on SDL_EVENT_QUIT
         */
        void PollEvents(bool& quit);
        
        /**
         * @brief Clear the screen with the specified color
         * @param r Red component (0-255)
         * @param g Green component (0-255)
         * @param b Blue component (0-255)
         * @param a Alpha component (0-255)
         */
        void Clear(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
        
        /**
         * @brief Present the rendered frame to the screen
         * 
         * Should be called after all drawing operations are complete.
         */
        void Present();
        
        /**
         * @brief Get the SDL renderer
         * @return Pointer to the SDL_Renderer
         */
        SDL_Renderer* GetRenderer() const { return m_Renderer; }
        
        /**
         * @brief Get the native SDL window
         * @return Pointer to the SDL_Window
         */
        SDL_Window* GetNativeWindow() const { return m_Window; }

    private:
        std::string m_Title;          ///< Window title
        int m_Width;                  ///< Window width in pixels
        int m_Height;                 ///< Window height in pixels
        SDL_Window* m_Window;         ///< SDL window handle
        SDL_Renderer* m_Renderer;     ///< SDL renderer handle
    };

}
