#pragma once

#include "../Graphics/Renderer.h"
#include "../Core/Input.h"
#include <string>
#include <vector>

namespace UI {

    class Widget {
    public:
        Widget(float x, float y, float w, float h) : X(x), Y(y), W(w), H(h) {}
        virtual ~Widget() {}

        virtual bool Update(float deltaTime) { return false; }
        virtual void Draw(Graphics::Renderer& renderer) = 0;

        float X, Y, W, H;
    };

}
