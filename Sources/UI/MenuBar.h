/**
 * MenuBar.h
 * Top menu bar UI component
 */

#pragma once

#include "Widget.h"
#include <vector>
#include <string>

namespace UI {

    /**
     * @class MenuBar
     * @brief Horizontal menu bar displaying menu items
     * 
     * Shows menu labels (File, Edit, View, Help) at the top of the window.
     * Currently displays static labels without dropdown functionality.
     */
    class MenuBar : public Widget {
    public:
        MenuBar(float x, float y, float w, float h) : Widget(x, y, w, h) {
            // Initialize default menus
            m_Menus.push_back("File");
            m_Menus.push_back("Edit");
            m_Menus.push_back("View");
            m_Menus.push_back("Help");
        }

        bool Update(float deltaTime) override {
            // Hover logic only for now, no dropdowns yet
            float mx = Core::Input::GetMouseX();
            float my = Core::Input::GetMouseY();
            return (my >= Y && my <= Y + H); // Consume input
        }

        void Draw(Graphics::Renderer& renderer) override {
            // Background
            renderer.SetColor(50, 50, 50, 255); // Slightly lighter than dark theme
            renderer.DrawRect(X, Y, W, H);

            float menuX = X + 10;
            for (const auto& menu : m_Menus) {
                renderer.SetColor(200, 200, 200, 255);
                renderer.DrawText(menuX, Y + (H - 8) / 2, menu);
                menuX += menu.length() * 8.0f + 20; // Spacing
            }
        }

    private:
        std::vector<std::string> m_Menus;
    };

}
