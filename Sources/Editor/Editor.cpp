/**
 * Editor.cpp
 * Implementation of the Editor class
 */

#include "Editor.h"
#include "../Core/Input.h"
#include <iostream>
#include <algorithm>

namespace Editor {

    Editor::Editor() : m_Root(nullptr), m_SelectedNode(nullptr), m_HoveredNode(nullptr), m_IsDragging(false), m_DragOffsetX(0), m_DragOffsetY(0) {
        // Create initial demo decision tree
        m_Root = new Data::TreeNode("Start", Data::NodeType::Start);
        Data::TreeNode* child1 = new Data::TreeNode("Is Ready?", Data::NodeType::Condition);
        Data::TreeNode* child2 = new Data::TreeNode("Do It", Data::NodeType::Action);
        
        m_Root->AddChild(child1); // Default label ""
        child1->AddChild(child2, "Yes"); // Labeled connection
        // Add a "No" branch
        Data::TreeNode* child3 = new Data::TreeNode("Wait", Data::NodeType::Action);
        child1->AddChild(child3, "No");

        // Calculate initial tree layout positions
        LayoutTree(m_Root, 600, 100, 300, 150);
    }

    Editor::~Editor() {
        if (m_Root) delete m_Root;
    }

    void Editor::Update(float deltaTime, bool inputCaptured) {
        float mouseX = Core::Input::GetMouseX();
        float mouseY = Core::Input::GetMouseY();

        // Determine which node (if any) is under the mouse cursor
        m_HoveredNode = HitTest(m_Root, mouseX, mouseY);
        
        // Update animation target scales based on hover state
        UpdateNodeScales(m_Root, m_HoveredNode);

        if (inputCaptured) return; // UI has captured input, skip editor interactions

        // Handle node selection and drag initiation
        if (Core::Input::IsMouseButtonPressed(1)) { // Left mouse button
            // Select the hovered node (or deselect if clicking empty space)
            m_SelectedNode = m_HoveredNode;
            
            if (m_SelectedNode) {
                m_IsDragging = true;
                m_DragOffsetX = m_SelectedNode->X - mouseX;
                m_DragOffsetY = m_SelectedNode->Y - mouseY;
            }
        }

        // Dragging
        if (m_IsDragging) {
            if (Core::Input::IsMouseButtonDown(1)) {
                if (m_SelectedNode) {
                    float newX = mouseX + m_DragOffsetX;
                    float newY = mouseY + m_DragOffsetY;
                    float deltaX = newX - m_SelectedNode->X;
                    float deltaY = newY - m_SelectedNode->Y;
                    
                    // Move Node
                    m_SelectedNode->X = newX;
                    m_SelectedNode->Y = newY;
                    
                    // Move Children Recursively (Select Tree Feature)
                    MoveTreeRecursive(m_SelectedNode, deltaX, deltaY);
                }
            } else {
                m_IsDragging = false;
            }
        }

        // Create child node on right-click (simplified context menu)
        if (Core::Input::IsMouseButtonPressed(3)) { // Right Click
            if (m_HoveredNode) {
                // Determine connection label based on parent type
                std::string connLabel = "";
                if (m_HoveredNode->Type == Data::NodeType::Condition) {
                    if (m_HoveredNode->Connections.empty()) connLabel = "Yes";
                    else if (m_HoveredNode->Connections.size() == 1) connLabel = "No";
                }

                Data::TreeNode* newChild = new Data::TreeNode("Action");
                newChild->X = m_HoveredNode->X + 50;
                newChild->Y = m_HoveredNode->Y + 100;
                m_HoveredNode->AddChild(newChild, connLabel);
            }
        }

        // Delete (Delete Key)
        if (Core::Input::IsKeyPressed(SDL_SCANCODE_DELETE) || Core::Input::IsKeyPressed(SDL_SCANCODE_BACKSPACE)) {
            DeleteSelected();
        }
    }

    void Editor::DeleteSelected() {
        if (m_SelectedNode && m_SelectedNode != m_Root) {
            DeleteNode(m_Root, m_SelectedNode);
            m_SelectedNode = nullptr;
            m_HoveredNode = nullptr;
            m_IsDragging = false;
        }
    }

    void Editor::CreateNode(Data::NodeType type) {
        Data::TreeNode* parent = m_SelectedNode ? m_SelectedNode : m_Root;
        if (!parent) return;

        std::string label = "Node";
        switch (type) {
            case Data::NodeType::Start: label = "Start"; break;
            case Data::NodeType::Action: label = "Action"; break;
            case Data::NodeType::Condition: label = "Cond"; break;
            case Data::NodeType::End: label = "End"; break;
        }
        
        // Auto-Label connection if parent is Condition
        std::string connLabel = "";
        if (parent->Type == Data::NodeType::Condition) {
             if (parent->Connections.empty()) connLabel = "Yes";
             else if (parent->Connections.size() == 1) connLabel = "No";
        }

        Data::TreeNode* newNode = new Data::TreeNode(label, type);
        newNode->X = parent->X + 50; // Simple offset
        newNode->Y = parent->Y + 120;
        parent->AddChild(newNode, connLabel);
        
        m_SelectedNode = newNode;
    }

    void Editor::Draw(Graphics::Renderer& renderer) {
        DrawNodeRecursive(renderer, m_Root);
    }

    void Editor::LayoutTree(Data::TreeNode* node, float x, float y, float hSpacing, float vSpacing) {
        if (!node) return;
        node->X = x;
        node->Y = y;
        if (!node->Connections.empty()) {
            float startX = x - ((node->Connections.size() - 1) * hSpacing) / 2.0f;
            for (size_t i = 0; i < node->Connections.size(); ++i) {
                LayoutTree(node->Connections[i].Target, startX + i * hSpacing, y + vSpacing, hSpacing / 2.0f, vSpacing);
            }
        }
    }

    void Editor::MoveTreeRecursive(Data::TreeNode* node, float dx, float dy) {
        if (!node) return;
        // Node itself is already moved by caller if it is the selected one.
        // But what if this is called recursively?
        // Let's assume caller moved 'node', we move children. 
        
        for (const auto& conn : node->Connections) {
            Data::TreeNode* child = conn.Target;
            if (child) {
                child->X += dx;
                child->Y += dy;
                MoveTreeRecursive(child, dx, dy);
            }
        }
    }

    void Editor::UpdateNodeScales(Data::TreeNode* node, Data::TreeNode* hovered) {
        if (!node) return;
        
        if (node == hovered) {
            node->TargetScale = 1.2f; // Scale up on hover
        } else {
            node->TargetScale = 1.0f; // Normal size
        }

        for (const auto& conn : node->Connections) {
            UpdateNodeScales(conn.Target, hovered);
        }
    }

    void Editor::DrawNodeRecursive(Graphics::Renderer& renderer, Data::TreeNode* node) {
        if (!node) return;

        // Animation Logic (Hack: Updating in Draw for simplicity, ideally in Update)
        // Simple Lerp: current += (target - current) * factor
        float lerpSpeed = 0.1f;
        node->Scale += (node->TargetScale - node->Scale) * lerpSpeed;

        // Draw connections first
        renderer.SetColor(200, 200, 200, 255);
        for (const auto& conn : node->Connections) {
            Data::TreeNode* child = conn.Target;
            if (!child) continue;

            // Bezier control points
            float cx1 = node->X;
            float cy1 = node->Y + 50;
            float cx2 = child->X;
            float cy2 = child->Y - 50;
            renderer.DrawBezier(node->X, node->Y, child->X, child->Y, cx1, cy1, cx2, cy2);

            // Draw Connection Label (Midpoint 0.5)
            if (!conn.Label.empty()) {
               // Calculate midpoint of bezier for text
               // Simple interp: 0.5
               float t = 0.5f;
               float u = 1 - t;
               float tt = t*t; 
               float uu = u*u;
               float uuu = uu*u;
               float ttt = tt*t;
               
               // Bezier func
               float mx = uuu * node->X + 3 * uu * t * cx1 + 3 * u * tt * cx2 + ttt * child->X;
               float my = uuu * node->Y + 3 * uu * t * cy1 + 3 * u * tt * cy2 + ttt * child->Y;

               renderer.SetColor(255, 255, 100, 255); // Yellowish text
               renderer.DrawText(mx, my, conn.Label);
               renderer.SetColor(200, 200, 200, 255); // Reset line color
            }

            DrawNodeRecursive(renderer, child);
        }

        // Draw Node
        renderer.DrawStyledNode(node->X, node->Y, node->Label, (node == m_SelectedNode), (int)node->Shape, node->R, node->G, node->B, node->Scale);
    }

    Data::TreeNode* Editor::HitTest(Data::TreeNode* node, float x, float y) {
        if (!node) return nullptr;

        float hitSize = 30.0f; // Approx visual size
        float dx = node->X - x;
        float dy = node->Y - y;
        
        // Simple box check for better hit testing on shapes
        if (std::abs(dx) < hitSize && std::abs(dy) < hitSize) {
            return node;
        }

        for (const auto& conn : node->Connections) {
            Data::TreeNode* hit = HitTest(conn.Target, x, y);
            if (hit) return hit;
        }

        return nullptr;
    }

    void Editor::DeleteNode(Data::TreeNode* parent, Data::TreeNode* nodeToDelete) {
        if (!parent) return;

        auto it = std::find_if(parent->Connections.begin(), parent->Connections.end(), 
            [&](const Data::Connection& c) { return c.Target == nodeToDelete; });
            
        if (it != parent->Connections.end()) {
            delete it->Target; // Destructor deletes children recursively
            parent->Connections.erase(it);
            return;
        }

        for (auto& conn : parent->Connections) {
            DeleteNode(conn.Target, nodeToDelete);
        }
    }

}
