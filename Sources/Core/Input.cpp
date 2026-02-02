#include "Input.h"
#include <cstring>

namespace Core {

    const bool* Input::m_KeyboardState = nullptr;
    std::vector<bool> Input::m_PrevKeyboardState;
    int Input::m_NumKeys = 0;

    Uint32 Input::m_MouseState = 0;
    Uint32 Input::m_PrevMouseState = 0;
    float Input::m_MouseX = 0;
    float Input::m_MouseY = 0;

    void Input::Update() {
        // Update keyboard
        if (!m_KeyboardState) {
            m_KeyboardState = SDL_GetKeyboardState(&m_NumKeys);
            m_PrevKeyboardState.resize(m_NumKeys, false);
        }

        for (int i = 0; i < m_NumKeys; ++i) {
            m_PrevKeyboardState[i] = m_KeyboardState[i];
        }

        // Update mouse
        m_PrevMouseState = m_MouseState;
        m_MouseState = SDL_GetMouseState(&m_MouseX, &m_MouseY);
    }

    void Input::ProcessEvent(const SDL_Event& e) {
        // SDL_GetKeyboardState updates automatically on PumpEvents
    }

    bool Input::IsKeyDown(SDL_Scancode key) {
        if (!m_KeyboardState) return false;
        return m_KeyboardState[key];
    }

    bool Input::IsKeyPressed(SDL_Scancode key) {
        if (!m_KeyboardState) return false;
        return m_KeyboardState[key] && !m_PrevKeyboardState[key];
    }

    bool Input::IsMouseButtonDown(int button) {
        return (m_MouseState & SDL_BUTTON_MASK(button));
    }

    bool Input::IsMouseButtonPressed(int button) {
        return (m_MouseState & SDL_BUTTON_MASK(button)) && !(m_PrevMouseState & SDL_BUTTON_MASK(button));
    }

    float Input::GetMouseX() {
        return m_MouseX;
    }

    float Input::GetMouseY() {
        return m_MouseY;
    }

}
