/**
 * Panel.h
 * Container panel widget for grouping UI elements
 */

#pragma once

#include "Widget.h"

namespace UI {

    /**
     * @class Panel
     * @brief Container widget that can hold child widgets
     * 
     * Provides a colored background panel that manages and renders child widgets.
     */
    class Panel : public Widget {
    public:
        Panel(float x, float y, float w, float h, uint8_t r, uint8_t g, uint8_t b) 
            : Widget(x, y, w, h), R(r), G(g), B(b) {}

        void AddChild(Widget* widget) {
            // Adjust child position relative to panel? No, absolute for simplicity for now.
            m_Children.push_back(widget);
        }

        bool Update(float deltaTime) override {
            bool handled = false;
            for (auto child : m_Children) {
                if (child->Update(deltaTime)) handled = true;
            }
            return handled;
        }

        void Draw(Graphics::Renderer& renderer) override {
            // Draw Background
            renderer.SetColor(R, G, B, 255);
            renderer.DrawRect(X, Y, W, H); // This draws outline in current Renderer implementation
            
            // Draw Content
            for (auto child : m_Children) {
                child->Draw(renderer);
            }
        }

    private:
        std::vector<Widget*> m_Children;
        uint8_t R, G, B;
    };

}
