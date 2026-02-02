/**
 * Button.h
 * Clickable button UI widget
 */

#pragma once

#include "Widget.h"
#include <functional>

namespace UI {

    /**
     * @class Button
     * @brief A clickable button with hover effects
     * 
     * Displays a labeled rectangle that can be clicked to trigger a callback.
     */
    class Button : public Widget {
    public:
        /**
         * @brief Construct a button
         * @param x X position
         * @param y Y position
         * @param w Width
         * @param h Height
         * @param label Button text label
         * @param onClick Callback function to invoke when clicked
         */
        Button(float x, float y, float w, float h, const std::string& label, std::function<void()> onClick) 
            : Widget(x, y, w, h), Label(label), OnClick(onClick), IsHovered(false) {}

        bool Update(float deltaTime) override {
            float mx = Core::Input::GetMouseX();
            float my = Core::Input::GetMouseY();

            // Check if mouse is over button
            IsHovered = (mx >= X && mx <= X + W && my >= Y && my <= Y + H);

            // Handle click
            if (IsHovered && Core::Input::IsMouseButtonPressed(1)) {
                if (OnClick) OnClick();
                return true; // Consumed input
            }
            return IsHovered; // Consume hover to block editor interaction
        }

        void Draw(Graphics::Renderer& renderer) override {
            if (IsHovered) {
                renderer.SetColor(100, 100, 200, 255);
            } else {
                renderer.SetColor(70, 70, 70, 255);
            }
            // Fill rect logic missing in Renderer, doing concentric rects for "fill" effect or just grid
            // For now, simple rect outline + center dot
            renderer.DrawRect(X, Y, W, H);
            
            // Draw Text
            renderer.SetColor(255, 255, 255, 255);
            // Center text: char width is 8, assume scale 1
            float textW = Label.length() * 8.0f;
            float textH = 8.0f;
            renderer.DrawText(X + (W - textW) / 2, Y + (H - textH) / 2, Label);
        }

    private:
        std::string Label;
        std::function<void()> OnClick;
        bool IsHovered;
    };

}
