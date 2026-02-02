/**
 * Input.cpp
 * Implementation of the Input management system
 */

#include "Input.h"
#include <cstring>

namespace Core {

    // Initialize static member variables
    const bool* Input::m_KeyboardState = nullptr;
    std::vector<bool> Input::m_PrevKeyboardState;
    int Input::m_NumKeys = 0;

    Uint32 Input::m_MouseState = 0;
    Uint32 Input::m_PrevMouseState = 0;
    float Input::m_MouseX = 0;
    float Input::m_MouseY = 0;

    void Input::Update() {
        // Initialize keyboard state on first call
        // SDL_GetKeyboardState returns a pointer to SDL's internal keyboard state array
        if (!m_KeyboardState) {
            m_KeyboardState = SDL_GetKeyboardState(&m_NumKeys);
            m_PrevKeyboardState.resize(m_NumKeys, false);
        }

        // Save current keyboard state as previous state for next frame
        // This allows us to detect key presses (down this frame, up last frame)
        for (int i = 0; i < m_NumKeys; ++i) {
            m_PrevKeyboardState[i] = m_KeyboardState[i];
        }

        // Update mouse button state and position
        // SDL_GetMouseState returns button state bitmask and updates position via pointers
        m_PrevMouseState = m_MouseState;
        m_MouseState = SDL_GetMouseState(&m_MouseX, &m_MouseY);
    }

    void Input::ProcessEvent(const SDL_Event& e) {
        // SDL_GetKeyboardState updates automatically on SDL_PumpEvents/SDL_PollEvent
        // This function is kept for potential future event processing needs
        // (e.g., text input, custom event handling, controller support)
    }

    bool Input::IsKeyDown(SDL_Scancode key) {
        if (!m_KeyboardState) return false;
        return m_KeyboardState[key];
    }

    bool Input::IsKeyPressed(SDL_Scancode key) {
        if (!m_KeyboardState) return false;
        // Key is pressed if it's down now but wasn't down last frame
        return m_KeyboardState[key] && !m_PrevKeyboardState[key];
    }

    bool Input::IsMouseButtonDown(int button) {
        // Check if the button bit is set in the current mouse state bitmask
        return (m_MouseState & SDL_BUTTON_MASK(button));
    }

    bool Input::IsMouseButtonPressed(int button) {
        // Button is pressed if it's down now but wasn't down last frame
        return (m_MouseState & SDL_BUTTON_MASK(button)) && !(m_PrevMouseState & SDL_BUTTON_MASK(button));
    }

    float Input::GetMouseX() {
        return m_MouseX;
    }

    float Input::GetMouseY() {
        return m_MouseY;
    }

}
