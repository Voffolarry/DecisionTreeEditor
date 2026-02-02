/**
 * Label.h
 * Simple text label UI widget
 */

#pragma once

#include "Widget.h"
#include <string>

namespace UI {

    /**
     * @class Label
     * @brief Non-interactive text label
     * 
     * Displays static text at a specified position.
     */
    class Label : public Widget {
    public:
        Label(float x, float y, const std::string& text) 
            : Widget(x, y, 0, 0), m_Text(text) {}

        bool Update(float deltaTime) override { return false; }

        void Draw(Graphics::Renderer& renderer) override {
            renderer.SetColor(255, 255, 255, 255);
            renderer.DrawText(X, Y, m_Text);
        }

    private:
        std::string m_Text;
    };

}
