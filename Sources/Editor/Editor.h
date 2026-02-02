#pragma once

#include "../Data/TreeNode.h"
#include "../Graphics/Renderer.h"
#include <vector>

namespace Editor {

    class Editor {
    public:
        Editor();
        ~Editor();

        void Update(float deltaTime, bool inputCaptured = false);
        void Draw(Graphics::Renderer& renderer);

        Data::TreeNode* GetRoot() { return m_Root; }
        Data::TreeNode* GetSelectedNode() { return m_SelectedNode; }
        void CreateNode(Data::NodeType type);
        void DeleteSelected();

    private:
        Data::TreeNode* m_Root;
        Data::TreeNode* m_SelectedNode;
        Data::TreeNode* m_HoveredNode;

        bool m_IsDragging;
        float m_DragOffsetX, m_DragOffsetY;

        void LayoutTree(Data::TreeNode* node, float x, float y, float hSpacing, float vSpacing);
        void MoveTreeRecursive(Data::TreeNode* node, float dx, float dy);
        void UpdateNodeScales(Data::TreeNode* node, Data::TreeNode* hovered);
        void DrawNodeRecursive(Graphics::Renderer& renderer, Data::TreeNode* node);
        Data::TreeNode* HitTest(Data::TreeNode* node, float x, float y);
        void DeleteNode(Data::TreeNode* parent, Data::TreeNode* nodeToDelete);
    };

}
