#include "Layout.h"
#include "../UI/TabBar.h"
#include "../UI/TextInput.h"
#include "../UI/Label.h"
#include "../UI/MenuBar.h"
#include <iostream>

namespace Editor {

    Layout::Layout(Editor* editor, float screenW, float screenH, SDL_Window* window) 
        : m_Editor(editor), m_ScreenW(screenW), m_ScreenH(screenH), m_Window(window) {
        
        float sidebarW = 200.0f;
        float inspectorW = 250.0f;

        // Menu Bar at very top
        float menuH = 25.0f;
        m_MenuBar = new UI::MenuBar(0, 0, screenW, menuH);

        // Left Sidebar (Palette)
        float topOffset = 35.0f; // TabBar Height
        float totalTopOffset = menuH + topOffset;
        
        m_LeftPanel = new UI::Panel(0, totalTopOffset, sidebarW, screenH - totalTopOffset, 37, 37, 38); 
        
        // Left Panel: Template Buttons
        float btnY = 50;
        float btnH = 40;
        float gap = 10;
        
        m_LeftPanel->AddChild(new UI::Button(20, btnY, 160, btnH, "Add Start", [=, this]() {
            m_Editor->CreateNode(Data::NodeType::Start);
        }));
        btnY += btnH + gap;

        m_LeftPanel->AddChild(new UI::Button(20, btnY, 160, btnH, "Add Action", [=, this]() {
            m_Editor->CreateNode(Data::NodeType::Action);
        }));
        btnY += btnH + gap;

        m_LeftPanel->AddChild(new UI::Button(20, btnY, 160, btnH, "Add Condition", [=, this]() {
            m_Editor->CreateNode(Data::NodeType::Condition);
        }));
        btnY += btnH + gap;

        m_LeftPanel->AddChild(new UI::Button(20, btnY, 160, btnH, "Add End", [=, this]() {
            m_Editor->CreateNode(Data::NodeType::End);
        }));

        // Right Sidebar (Inspector)
        m_RightPanel = new UI::Panel(screenW - inspectorW, totalTopOffset, inspectorW, screenH - totalTopOffset, 37, 37, 38);
        
        // Add Inspector controls
        m_RightPanel->AddChild(new UI::Button(screenW - inspectorW + 20, 50, 210, 40, "Delete Selected", [=, this]() {
           m_Editor->DeleteSelected();
        }));

        // Label Edit
        m_RightPanel->AddChild(new UI::Label(screenW - inspectorW + 20, 100, "Node Label:")); 
        
        m_LabelInput = new UI::TextInput(screenW - inspectorW + 20, 120, 210, 30, nullptr, m_Window);
        m_RightPanel->AddChild(m_LabelInput);

        // Top Tab Bar (Below Menu Bar)
        m_TabBar = new UI::TabBar(0, menuH, screenW, topOffset); 

        m_UIElements.push_back(m_MenuBar); 
        m_UIElements.push_back(m_TabBar); 
        m_UIElements.push_back(m_LeftPanel);
        m_UIElements.push_back(m_RightPanel);
    }

    Layout::~Layout() {
        for (auto ui : m_UIElements) {
            delete ui; // Recursive delete of children if Panel handled ownership, but here simple vector
        }
    }

    bool Layout::Update(float deltaTime) {
        // Update selection binding
        Data::TreeNode* selected = m_Editor->GetSelectedNode();
        if (m_LabelInput) {
            // Only update target if NOT focused to allow external rename? 
            // Better: update always, but maybe careful if typing.
            // Actually binding pointer is safe.
            m_LabelInput->SetTarget(selected ? &selected->Label : nullptr);
        }

        bool handled = false;
        for (auto ui : m_UIElements) {
            if (ui->Update(deltaTime)) handled = true;
        }
        return handled;
    }

    void Layout::Draw(Graphics::Renderer& renderer) {
        // Draw Editor (Canvas) in the middle
        // We might want to clip or offset the Editor view to the space between panels
        // For now, full screen draw behind panels
        m_Editor->Draw(renderer);

        // Draw UI on top
        for (auto ui : m_UIElements) {
            ui->Draw(renderer);
        }
    }

    void Layout::ProcessTextInput(const char* text) {
        if (m_LabelInput) {
            m_LabelInput->AppendText(text);
        }
    }

}
