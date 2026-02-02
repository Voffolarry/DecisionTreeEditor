/**
 * Renderer.h
 * High-level rendering abstraction for decision tree visuals
 * 
 * Provides drawing primitives for shapes, text, and styled nodes.
 * Wraps SDL3 rendering functionality with a cleaner interface.
 */

#pragma once

#include <SDL3/SDL.h>
#include <string>

namespace Graphics {

    /**
     * @class Renderer
     * @brief Rendering interface for drawing shapes and text
     * 
     * Provides high-level drawing methods including lines, Bezier curves,
     * shapes (circles, rectangles, diamonds, capsules), text, and complete
     * styled decision tree nodes.
     */
    class Renderer {
    public:
        Renderer(SDL_Renderer* renderer);
        ~Renderer();

        // Line drawing
        void DrawLine(float x1, float y1, float x2, float y2);
        void DrawBezier(float x1, float y1, float x2, float y2, float cx1, float cy1, float cx2, float cy2);
        
        // Shape outlines
        void DrawCircle(float x, float y, float radius);
        void DrawRect(float x, float y, float w, float h);
        void DrawDiamond(float x, float y, float w, float h);
        void DrawCapsule(float x, float y, float w, float h);
        
        // Filled shapes
        void FillRect(float x, float y, float w, float h);
        void FillDiamond(float x, float y, float w, float h);
        void FillCapsule(float x, float y, float w, float h);
        void FillCircle(float x, float y, float radius);

        /**
         * @brief Draw a complete styled decision tree node
         * @param x Center X position
         * @param y Center Y position
         * @param label Text label for the node
         * @param isSelected Whether node is selected (draws with highlight)
         * @param shapeType Shape type (0=Circle, 1=Rectangle, 2=Diamond, 3=Capsule)
         * @param r Red color component
         * @param g Green color component
         * @param b Blue color component
         * @param scale Scale factor for animation
         */
        void DrawStyledNode(float x, float y, const std::string& label, bool isSelected, int shapeType, uint8_t r, uint8_t g, uint8_t b, float scale = 1.0f);
        
        /**
         * @brief Draw text using the simple bitmap font
         * @param x X position (top-left)
         * @param y Y position (top-left)
         * @param text Text string to draw
         * @param scale Scale factor for text size
         */
        void DrawText(float x, float y, const std::string& text, float scale = 1.0f);

        /**
         * @brief Set the current drawing color
         * @param r Red (0-255)
         * @param g Green (0-255)
         * @param b Blue (0-255)
         * @param a Alpha (0-255)
         */
        void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

    private:
        SDL_Renderer* m_Renderer;         ///< SDL renderer handle
        uint8_t m_R, m_G, m_B, m_A;       ///< Cached color for geometry rendering
    };

}
