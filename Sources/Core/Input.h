#pragma once

#include <SDL3/SDL.h>
#include <vector>

namespace Core {

    class Input {
    public:
        static void Update();
        static void ProcessEvent(const SDL_Event& e);

        static bool IsKeyDown(SDL_Scancode key);
        static bool IsKeyPressed(SDL_Scancode key);

        static bool IsMouseButtonDown(int button); // 1: Left, 2: Middle, 3: Right
        static bool IsMouseButtonPressed(int button);

        static float GetMouseX();
        static float GetMouseY();

    private:
        static const bool* m_KeyboardState;
        static std::vector<bool> m_PrevKeyboardState;
        static int m_NumKeys;

        static Uint32 m_MouseState;
        static Uint32 m_PrevMouseState;
        static float m_MouseX, m_MouseY;
    };

}
