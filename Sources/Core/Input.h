/**
 * Input.h
 * Input management system for keyboard and mouse interaction
 * 
 * Provides a centralized input handling system that tracks keyboard and mouse states
 * across frames, enabling both "down" (current state) and "pressed" (state change) queries.
 */

#pragma once

#include <SDL3/SDL.h>
#include <vector>

namespace Core {

    /**
     * @class Input
     * @brief Static input manager for keyboard and mouse input
     * 
     * This class provides a unified interface for querying keyboard and mouse input states.
     * It maintains both current and previous frame states to detect button presses
     * (transitions from up to down) versus continuous holds.
     * 
     * Usage:
     * - Call Update() at the start of each frame to snapshot the previous state
     * - Call ProcessEvent() for each SDL event
     * - Query input states using IsKeyDown(), IsKeyPressed(), etc.
     */

    class Input {
    public:
        /**
         * @brief Update input state for the current frame
         * 
         * Should be called once per frame before processing SDL events.
         * Snapshots the current state as the "previous" state for next frame comparisons.
         */
        static void Update();
        
        /**
         * @brief Process an SDL event
         * @param e The SDL event to process
         * 
         * Currently a no-op as SDL_GetKeyboardState auto-updates on SDL_PumpEvents.
         * Kept for future extension (e.g., text input, custom event handling).
         */
        static void ProcessEvent(const SDL_Event& e);

        /**
         * @brief Check if a key is currently held down
         * @param key The SDL scancode of the key to check
         * @return true if the key is currently down, false otherwise
         */
        static bool IsKeyDown(SDL_Scancode key);
        
        /**
         * @brief Check if a key was just pressed this frame
         * @param key The SDL scancode of the key to check
         * @return true if the key transitioned from up to down this frame
         */
        static bool IsKeyPressed(SDL_Scancode key);

        /**
         * @brief Check if a mouse button is currently held down
         * @param button Mouse button index (1: Left, 2: Middle, 3: Right)
         * @return true if the button is currently down
         */
        static bool IsMouseButtonDown(int button);
        
        /**
         * @brief Check if a mouse button was just pressed this frame
         * @param button Mouse button index (1: Left, 2: Middle, 3: Right)
         * @return true if the button transitioned from up to down this frame
         */
        static bool IsMouseButtonPressed(int button);

        /**
         * @brief Get the current mouse X position
         * @return Mouse X coordinate in window space
         */
        static float GetMouseX();
        
        /**
         * @brief Get the current mouse Y position
         * @return Mouse Y coordinate in window space
         */
        static float GetMouseY();

    private:
        // Keyboard state tracking
        static const bool* m_KeyboardState;        ///< Current keyboard state from SDL
        static std::vector<bool> m_PrevKeyboardState; ///< Previous frame's keyboard state
        static int m_NumKeys;                      ///< Total number of keys tracked

        // Mouse state tracking
        static Uint32 m_MouseState;                ///< Current mouse button state bitmask
        static Uint32 m_PrevMouseState;            ///< Previous frame's mouse button state
        static float m_MouseX, m_MouseY;           ///< Current mouse position
    };

}
