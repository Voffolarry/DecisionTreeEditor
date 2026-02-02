#pragma once

#include <SDL3/SDL.h>
#include <string>

namespace Graphics {

    class Renderer {
    public:
        Renderer(SDL_Renderer* renderer);
        ~Renderer();

        void DrawLine(float x1, float y1, float x2, float y2);
        void DrawBezier(float x1, float y1, float x2, float y2, float cx1, float cy1, float cx2, float cy2);
        void DrawCircle(float x, float y, float radius);
        void DrawStyledNode(float x, float y, const std::string& label, bool isSelected, int shapeType, uint8_t r, uint8_t g, uint8_t b, float scale = 1.0f);
        void DrawText(float x, float y, const std::string& text, float scale = 1.0f);
        void DrawRect(float x, float y, float w, float h);
        void DrawDiamond(float x, float y, float w, float h);
        void DrawCapsule(float x, float y, float w, float h);
        
        // Filled Primitives
        void FillRect(float x, float y, float w, float h);
        void FillDiamond(float x, float y, float w, float h);
        void FillCapsule(float x, float y, float w, float h);
        void FillCircle(float x, float y, float radius);

        void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

    private:
        SDL_Renderer* m_Renderer;
        // Cache color for SDL_RenderGeometry vertices
        uint8_t m_R, m_G, m_B, m_A;
    };

}
