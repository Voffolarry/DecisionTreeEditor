/**
 * Layout.h
 * Main layout manager coordinating UI and editor
 */

#pragma once

#include "../UI/Panel.h"
#include "../UI/Button.h"
#include "Editor.h"

namespace UI { class TextInput; }

namespace Editor {

    /**
     * @class Layout
     * @brief Manages the overall UI layout and editor composition
     * 
     * Coordinates all UI panels (menu bar, tab bar, side panels, buttons)
     * with the editor viewport. Handles input routing and rendering order.
     */
    class Layout {
    public:
        Layout(Editor* editor, float screenW, float screenH, SDL_Window* window);
        ~Layout();

        bool Update(float deltaTime);
        void Draw(Graphics::Renderer& renderer);
        void ProcessTextInput(const char* text);

    private:
        Editor* m_Editor;
        float m_ScreenW, m_ScreenH;
        SDL_Window* m_Window;

        UI::Panel* m_LeftPanel;
        UI::Panel* m_RightPanel;
        UI::Widget* m_TabBar;
        UI::Widget* m_MenuBar;
        
        UI::TextInput* m_LabelInput;

        std::vector<UI::Widget*> m_UIElements;
    };

}
