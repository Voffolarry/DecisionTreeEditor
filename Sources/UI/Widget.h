/**
 * Widget.h
 * Base class for all UI widgets
 * 
 * Defines the interface that all UI components must implement,
 * including update logic and rendering.
 */

#pragma once

#include "../Graphics/Renderer.h"
#include "../Core/Input.h"
#include <string>
#include <vector>

namespace UI {

    /**
     * @class Widget
     * @brief Abstract base class for UI widgets
     * 
     * All UI components inherit from this class and must implement
     * the Draw() method. Update() can optionally be overridden.
     */
    class Widget {
    public:
        Widget(float x, float y, float w, float h) : X(x), Y(y), W(w), H(h) {}
        virtual ~Widget() {}

        /**
         * @brief Update widget state
         * @param deltaTime Time since last frame
         * @return true if widget consumed input (prevents passthrough)
         */
        virtual bool Update(float deltaTime) { return false; }
        
        /**
         * @brief Render the widget
         * @param renderer The renderer to draw with
         */
        virtual void Draw(Graphics::Renderer& renderer) = 0;

        float X, Y, W, H;  ///< Widget position and dimensions
    };

}
