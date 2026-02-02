#include "Renderer.h"
#include "SimpleFont.h"
#include <cmath>

namespace Graphics {

    Renderer::Renderer(SDL_Renderer* renderer) : m_Renderer(renderer) {
    }

    Renderer::~Renderer() {
    }

    void Renderer::DrawLine(float x1, float y1, float x2, float y2) {
        SDL_RenderLine(m_Renderer, x1, y1, x2, y2);
    }

    void Renderer::DrawBezier(float x1, float y1, float x2, float y2, float cx1, float cy1, float cx2, float cy2) {
        float t = 0;
        float step = 0.05f;
        float prevX = x1;
        float prevY = y1;

        while (t <= 1.0f) {
            float u = 1 - t;
            float tt = t * t;
            float uu = u * u;
            float uuu = uu * u;
            float ttt = tt * t;

            float x = uuu * x1 + 3 * uu * t * cx1 + 3 * u * tt * cx2 + ttt * x2;
            float y = uuu * y1 + 3 * uu * t * cy1 + 3 * u * tt * cy2 + ttt * y2;

            SDL_RenderLine(m_Renderer, prevX, prevY, x, y);
            prevX = x;
            prevY = y;
            t += step;
        }
        SDL_RenderLine(m_Renderer, prevX, prevY, x2, y2);
    }

    void Renderer::DrawCircle(float x, float y, float radius) {
        // Simple circle drawing algorithm
        for (int w = 0; w < radius * 2; w++) {
            for (int h = 0; h < radius * 2; h++) {
                int dx = radius - w; // horizontal offset
                int dy = radius - h; // vertical offset
                if ((dx*dx + dy*dy) <= (radius * radius)) {
                    SDL_RenderPoint(m_Renderer, x + dx, y + dy);
                }
            }
        }
    }

    void Renderer::DrawStyledNode(float x, float y, const std::string& label, bool isSelected, int shapeType, uint8_t r, uint8_t g, uint8_t b, float scale) {
        float baseSize = 50.0f;
        float size = baseSize * scale;
        
        // Glow/Outline if selected
        if (isSelected) {
            SetColor(255, 215, 0, 255); // Gold outline
            // Draw slightly larger primitive behind
            switch (shapeType) {
                case 1: FillRect(x - size/2 - 2, y - size/2 - 2, size + 4, size + 4); break; // Rectangle
                case 2: FillDiamond(x, y, size + 6, size + 6); break; // Diamond
                case 3: FillCapsule(x, y, size * 2 + 4, size + 4); break; // Capsule
                default: FillCircle(x, y, (size/2) + 2); break; // Circle
            }
        }

        // Main Body (Filled)
        SetColor(r, g, b, 255);
        
        switch (shapeType) {
            case 1: FillRect(x - size/2, y - size/2, size, size); break;
            case 2: FillDiamond(x, y, size, size); break;
            case 3: FillCapsule(x, y, size * 2, size); break;
            default: FillCircle(x, y, size/2); break;
        }

        // Border (Optional, slightly darker or white)
        SetColor(255, 255, 255, 150);
        switch (shapeType) {
            case 1: DrawRect(x - size/2, y - size/2, size, size); break;
            case 2: DrawDiamond(x, y, size, size); break;
            case 3: DrawCapsule(x, y, size * 2, size); break;
            default: DrawCircle(x, y, size/2); break;
        }

        // Draw Label
        SetColor(255, 255, 255, 255);
        // Center label roughly
        DrawText(x - (label.length() * 4), y - 4, label); 
    }

    // --- Fill Implementations ---

    void Renderer::FillRect(float x, float y, float w, float h) {
        SDL_FRect rect = { x, y, w, h };
        SDL_RenderFillRect(m_Renderer, &rect);
    }

    void Renderer::FillDiamond(float x, float y, float w, float h) {
        // Diamond = 2 Triangles
        float halfW = w/2;
        float halfH = h/2;
        
        // Vertices: Top, Right, Bottom, Left
        SDL_Vertex v[4];
        
        // Center-Top
        v[0].position = { x, y - halfH };
        v[0].color = { m_R / 255.0f, m_G / 255.0f, m_B / 255.0f, m_A / 255.0f };
        v[0].tex_coord = { 0, 0 };

        // Center-Right
        v[1].position = { x + halfW, y };
        v[1].color = { m_R / 255.0f, m_G / 255.0f, m_B / 255.0f, m_A / 255.0f };
        v[1].tex_coord = { 0, 0 };

        // Center-Bottom
        v[2].position = { x, y + halfH };
        v[2].color = { m_R / 255.0f, m_G / 255.0f, m_B / 255.0f, m_A / 255.0f };
        v[2].tex_coord = { 0, 0 };

        // Center-Left
        v[3].position = { x - halfW, y };
        v[3].color = { m_R / 255.0f, m_G / 255.0f, m_B / 255.0f, m_A / 255.0f };
        v[3].tex_coord = { 0, 0 };

        // Indices for 2 triangles: 0-1-3 and 1-2-3 (or similar)
        // Wait, standard order is usually clockwise? 
        // T1: Top, Right, Left -> 0, 1, 3
        // T2: Right, Bottom, Left -> 1, 2, 3
        int indices[] = { 0, 1, 3, 1, 2, 3 };
        
        SDL_RenderGeometry(m_Renderer, nullptr, v, 4, indices, 6);
    }

    void Renderer::FillCapsule(float x, float y, float w, float h) {
        float radius = h / 2;
        float rectW = w - 2 * radius;
        
        // Center Rect
        FillRect(x - rectW/2, y - radius, rectW, h);
        
        // Left Circle
        FillCircle(x - rectW/2, y, radius);
        
        // Right Circle
        FillCircle(x + rectW/2, y, radius);
    }

    void Renderer::FillCircle(float x, float y, float radius) {
        // Fan of triangles approximation
        // Or scanline. For SDL3 without GPU custom shaders, scanline is easy-ish or multiple rects/points.
        // SDL_RenderGeometry approach:
        const int valid_radius = (int)radius;
        if (valid_radius <= 0) return;

        // Simple scanline fill
        for (int w = 0; w < valid_radius * 2; w++) {
            for (int h = 0; h < valid_radius * 2; h++) {
                int dx = valid_radius - w;
                int dy = valid_radius - h;
                if ((dx*dx + dy*dy) <= (valid_radius * valid_radius)) {
                    SDL_RenderPoint(m_Renderer, x + dx, y + dy);
                }
            }
        }
        // Improve: Use standard midpoint circle algorithm to draw lines for filling (faster than points)
    }

    // --- Wireframe Implementations (Optimized) ---

    void Renderer::DrawDiamond(float x, float y, float w, float h) {
        float halfW = w / 2;
        float halfH = h / 2;
        DrawLine(x, y - halfH, x + halfW, y);
        DrawLine(x + halfW, y, x, y + halfH);
        DrawLine(x, y + halfH, x - halfW, y);
        DrawLine(x - halfW, y, x, y - halfH);
    }

    void Renderer::DrawCapsule(float x, float y, float w, float h) {
        float radius = h / 2;
        float rectW = w - 2 * radius;
        DrawLine(x - rectW/2, y - radius, x + rectW/2, y - radius);
        DrawLine(x - rectW/2, y + radius, x + rectW/2, y + radius);
        // Curves - simple lines for now:
        DrawLine(x - rectW/2, y - radius, x - rectW/2 - radius, y);
        DrawLine(x - rectW/2 - radius, y, x - rectW/2, y + radius);
        DrawLine(x + rectW/2, y - radius, x + rectW/2 + radius, y);
        DrawLine(x + rectW/2 + radius, y, x + rectW/2, y + radius);
    }

    void Renderer::DrawText(float x, float y, const std::string& text, float scale) {
        for (char c : text) {
            if (c < 32 || c > 127) c = '?';
            const uint8_t* glyph = font8x8_basic[c - 32];

            for (int row = 0; row < 8; ++row) {
                for (int col = 0; col < 8; ++col) {
                    if (glyph[row] & (1 << (7 - col))) {
                        // Pixel on
                        if (scale == 1.0f) {
                            SDL_RenderPoint(m_Renderer, x + col, y + row);
                        } else {
                            SDL_FRect rect = { x + col * scale, y + row * scale, scale, scale };
                            SDL_RenderRect(m_Renderer, &rect);
                        }
                    }
                }
            }
            x += 8 * scale;
        }
    }



    void Renderer::DrawRect(float x, float y, float w, float h) {
        SDL_FRect rect = { x, y, w, h };
        SDL_RenderRect(m_Renderer, &rect);
    }

    void Renderer::SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        m_R = r; m_G = g; m_B = b; m_A = a;
        SDL_SetRenderDrawColor(m_Renderer, r, g, b, a);
    }

}
