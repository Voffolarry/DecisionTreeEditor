/**
 * Editor.h
 * Core editor functionality for manipulating decision trees
 * 
 * Provides the main editor logic including node selection, drag-and-drop,
 * tree layout, hit-testing, and node creation/deletion operations.
 */

#pragma once

#include "../Data/TreeNode.h"
#include "../Graphics/Renderer.h"
#include <vector>

namespace Editor {

    /**
     * @class Editor
     * @brief Main editor class for decision tree manipulation
     * 
     * Manages the decision tree state, user interactions (selection, dragging),
     * and provides operations for creating and deleting nodes. Works in
     * conjunction with the Layout class for UI integration.
     */
    class Editor {
    public:
        Editor();
        ~Editor();

        /**
         * @brief Update editor state and handle input
         * @param deltaTime Time since last frame (currently unused)
         * @param inputCaptured Whether UI has captured input (prevents editor input)
         * 
         * Handles mouse hover, selection, dragging, and keyboard shortcuts.
         */
        void Update(float deltaTime, bool inputCaptured = false);
        
        /**
         * @brief Render the decision tree
         * @param renderer The renderer to draw with
         */
        void Draw(Graphics::Renderer& renderer);

        Data::TreeNode* GetRoot() { return m_Root; }
        Data::TreeNode* GetSelectedNode() { return m_SelectedNode; }
        
        /**
         * @brief Create a new child node attached to the selected node
         * @param type The type of node to create
         */
        void CreateNode(Data::NodeType type);
        
        /**
         * @brief Delete the currently selected node (cannot delete root)
         */
        void DeleteSelected();

    private:
        Data::TreeNode* m_Root;           ///< Root node of the decision tree
        Data::TreeNode* m_SelectedNode;   ///< Currently selected node (can be null)
        Data::TreeNode* m_HoveredNode;    ///< Node under mouse cursor (can be null)

        // Drag state
        bool m_IsDragging;                ///< Whether user is dragging a node
        float m_DragOffsetX, m_DragOffsetY; ///< Offset from mouse to node center

        // Helper methods
        void LayoutTree(Data::TreeNode* node, float x, float y, float hSpacing, float vSpacing);
        void MoveTreeRecursive(Data::TreeNode* node, float dx, float dy);
        void UpdateNodeScales(Data::TreeNode* node, Data::TreeNode* hovered);
        void DrawNodeRecursive(Graphics::Renderer& renderer, Data::TreeNode* node);
        Data::TreeNode* HitTest(Data::TreeNode* node, float x, float y);
        void DeleteNode(Data::TreeNode* parent, Data::TreeNode* nodeToDelete);
    };

}
