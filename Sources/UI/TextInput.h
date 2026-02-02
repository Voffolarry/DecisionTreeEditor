/**
 * TextInput.h
 * Editable text input field widget
 */

#pragma once

#include "Widget.h"
#include <string>
#include <iostream>
#include <SDL3/SDL.h>

namespace UI {

    /**
     * @class TextInput
     * @brief Single-line text input widget with focus and cursor
     * 
     * Provides a clickable text field that accepts keyboard input when focused.
     * Handles text input events and displays a blinking cursor.
     */
    class TextInput : public Widget {
    public:
        TextInput(float x, float y, float w, float h, std::string* targetString, SDL_Window* window) 
            : Widget(x, y, w, h), m_Target(targetString), m_Window(window), m_IsFocused(false) {}

        void SetTarget(std::string* target) {
            m_Target = target;
        }

        bool Update(float deltaTime) override {
            float mx = Core::Input::GetMouseX();
            float my = Core::Input::GetMouseY();
            bool hovered = (mx >= X && mx <= X + W && my >= Y && my <= Y + H);
            bool handled = false;

            if (Core::Input::IsMouseButtonPressed(1)) {
                if (hovered) {
                    m_IsFocused = true;
                    SDL_StartTextInput(m_Window);
                    handled = true;
                } else {
                     // If clicked outside, lose focus? 
                     // Only if we don't want "click anywhere to deselect" logic to interfere.
                     // But here we return handled=true only if we clicked THE WIDGET.
                     if (m_IsFocused) {
                         m_IsFocused = false;
                         SDL_StopTextInput(m_Window);
                     }
                }
            }
            
            // FIXME: This is a placeholder for real text input, simulating backspace at least.
            if (m_IsFocused && m_Target) {
                 if (Core::Input::IsKeyPressed(SDL_SCANCODE_BACKSPACE) && !m_Target->empty()) {
                     m_Target->pop_back();
                 }
                 // Consume keyboard if focused
                 handled = true; 
            }
            
            return handled || (hovered && Core::Input::IsMouseButtonPressed(1));
        }

        // We need a helper to append text from SDL Events in Main
        void AppendText(const char* text) {
            if (m_IsFocused && m_Target) {
                *m_Target += text;
            }
        }

        void Draw(Graphics::Renderer& renderer) override {
            // Background
            if (m_IsFocused) {
                renderer.SetColor(20, 20, 20, 255);
            } else {
                renderer.SetColor(30, 30, 30, 255);
            }
            renderer.FillRect(X, Y, W, H);
            
            // Border
            renderer.SetColor(m_IsFocused ? 0 : 100, m_IsFocused ? 122 : 100, m_IsFocused ? 204 : 100, 255);
            renderer.DrawRect(X, Y, W, H);

            // Text
            if (m_Target) {
                renderer.SetColor(255, 255, 255, 255);
                renderer.DrawText(X + 5, Y + (H - 8) / 2, *m_Target);
                
                // Cursor
                if (m_IsFocused) {
                    float tw = m_Target->length() * 8.0f;
                    renderer.DrawLine(X + 5 + tw + 2, Y + 4, X + 5 + tw + 2, Y + H - 4);
                }
            }
        }

    private:
        std::string* m_Target;
        SDL_Window* m_Window;
        bool m_IsFocused;
    };

}
