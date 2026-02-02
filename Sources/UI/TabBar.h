/**
 * TabBar.h
 * Tab bar widget for managing multiple open files
 */

#pragma once

#include "Widget.h"
#include <vector>
#include <string>
#include <algorithm>

namespace UI {

    /**
     * @class TabBar
     * @brief Tab bar with drag-to-reorder and add functionality
     * 
     * Displays horizontal tabs that can be clicked to switch between,
     * dragged to reorder, and added with the "+" button.
     */
    class TabBar : public Widget {
    public:
        TabBar(float x, float y, float w, float h) : Widget(x, y, w, h), m_ActiveTab(0), m_IsDragging(false), m_DragIndex(-1) {
            // Initialize with default tabs
            m_Tabs.push_back("DecisionTree.json");
            m_Tabs.push_back("Settings.json"); 
        }

        bool Update(float deltaTime) override {
            float mx = Core::Input::GetMouseX();
            float my = Core::Input::GetMouseY();
            float tabW = 150.0f;
            bool handled = false;

            // Handle "Add Tab" button click
            float addBtnX = X + m_Tabs.size() * tabW + 5;
            if (my >= Y && my <= Y + H && mx >= addBtnX && mx <= addBtnX + 20) {
                 if (Core::Input::IsMouseButtonPressed(1)) {
                     m_Tabs.push_back("New Tab");
                     m_ActiveTab = m_Tabs.size() - 1;
                     return true; // Consumed input
                 }
            }

            // Continue dragging if mouse is held down
            if (m_IsDragging) {
                if (Core::Input::IsMouseButtonDown(1)) {
                    // Swap tabs if dragged over a different tab
                    int hoverIndex = (int)((mx - X) / tabW);
                    if (hoverIndex >= 0 && hoverIndex < m_Tabs.size() && hoverIndex != m_DragIndex) {
                        std::iter_swap(m_Tabs.begin() + m_DragIndex, m_Tabs.begin() + hoverIndex);
                        
                        // Update selection if we swapped selected
                        if (m_ActiveTab == m_DragIndex) m_ActiveTab = hoverIndex;
                        else if (m_ActiveTab == hoverIndex) m_ActiveTab = m_DragIndex;
                        
                        m_DragIndex = hoverIndex; // Update tracked index
                    }
                    handled = true;
                } else {
                    m_IsDragging = false;
                    m_DragIndex = -1;
                    handled = true;
                }
            } else {
                if (my >= Y && my <= Y + H && Core::Input::IsMouseButtonPressed(1)) {
                    int index = (int)((mx - X) / tabW);
                    if (index >= 0 && index < m_Tabs.size()) {
                        m_ActiveTab = index;
                        m_IsDragging = true;
                        m_DragIndex = index;
                        handled = true;
                    }
                }
            }
            
            if (my >= Y && my <= Y + H) handled = true; // Swallow
            return handled;
        }

        void Draw(Graphics::Renderer& renderer) override {
            // Background
            renderer.SetColor(37, 37, 38, 255); 
            renderer.FillRect(X, Y, W, H); // FillRect now available? 
            // Renderer checks: DrawRect is outline. FillRect?
            // Renderer.h has FillRect (impl in previous steps). Let's use Rect for now or FillRect if confirmed.
            // Wait, previous Renderer had FillRect.
            // Using FillRect for background.

            float tabW = 150.0f;
            for (size_t i = 0; i < m_Tabs.size(); ++i) {
                float tx = X + i * tabW;
                
                // Active Tab Highlight
                if (i == m_ActiveTab) {
                    renderer.SetColor(30, 30, 30, 255); 
                } else {
                    renderer.SetColor(45, 45, 45, 255); 
                }
                renderer.FillRect(tx, Y, tabW, H); 
                renderer.SetColor(0, 0, 0, 255); // Border separation
                renderer.DrawRect(tx, Y, tabW, H);

                // Top accent line
                if (i == m_ActiveTab) {
                    renderer.SetColor(0, 122, 204, 255); 
                    renderer.FillRect(tx, Y, tabW, 2); 
                }
                
                renderer.SetColor(220, 220, 220, 255);
                renderer.DrawText(tx + 10, Y + 12, m_Tabs[i]);
            }

            // Draw Add Button
            float addBtnX = X + m_Tabs.size() * tabW + 5;
            renderer.SetColor(60, 60, 60, 255);
            renderer.FillRect(addBtnX, Y + 5, 20, 20);
            renderer.SetColor(200, 200, 200, 255);
            renderer.DrawText(addBtnX + 6, Y + 10, "+");
        }

    private:
        std::vector<std::string> m_Tabs;
        int m_ActiveTab;
        bool m_IsDragging;
        int m_DragIndex;
    };

}
