/**
 * TreeNode.h
 * Core data structures for decision tree nodes
 * 
 * Defines the data model for decision tree nodes, including node types,
 * visual shapes, connections between nodes, and all associated properties
 * for layout, animation, and rendering.
 */

#pragma once

#include <string>
#include <vector>
#include <functional>
#include <cstdint>

namespace Data {

    /**
     * @enum NodeType
     * @brief Semantic type of a decision tree node
     * 
     * Determines the logical role of a node in the decision tree.
     * Each type has default visual properties (shape and color).
     */
    enum class NodeType {
        Start,      ///< Entry point of the decision tree
        Action,     ///< Action or operation node
        Condition,  ///< Decision/branching node
        End         ///< Terminal node
    };

    /**
     * @enum ShapeType
     * @brief Visual shape used to render a node
     */
    enum class ShapeType {
        Circle,     ///< Circular shape
        Rectangle,  ///< Rectangular shape
        Diamond,    ///< Diamond shape (typically for conditions)
        Capsule     ///< Rounded capsule shape
    };

    struct TreeNode; // Forward declaration

    /**
     * @struct Connection
     * @brief Represents a directed edge to a child node
     */
    struct Connection {
        TreeNode* Target;        ///< Pointer to the target child node
        std::string Label;       ///< Label displayed on the connection edge
    };

    /**
     * @struct TreeNode
     * @brief A node in the decision tree
     * 
     * Contains all data for a single node including its label, type, visual properties,
     * layout position, animation state, and connections to child nodes.
     * Manages ownership of child nodes through the Connections vector.
     */
    struct TreeNode {
        // Core data
        std::string Label;                    ///< Display label for the node
        std::vector<Connection> Connections;  ///< Child nodes and their edge labels
        bool IsLeaf;                          ///< Deprecated: whether node has children
        NodeType Type;                        ///< Semantic type of the node
        ShapeType Shape;                      ///< Visual shape for rendering
        
        // Visual properties
        uint8_t R, G, B;                      ///< RGB color values (0-255)

        // Layout properties
        float X, Y;                           ///< Position in screen space
        
        // Animation properties
        float Scale;                          ///< Current scale (for animation)
        float TargetScale;                    ///< Target scale (animated toward)

        /**
         * @brief Construct a new TreeNode
         * @param label Display label for the node
         * @param type Semantic type (determines default shape and color)
         * 
         * Initializes a new node with type-specific defaults:
         * - Start: Green capsule
         * - Action: Blue rectangle
         * - Condition: Orange diamond
         * - End: Red capsule
         */
        TreeNode(const std::string& label, NodeType type = NodeType::Action) 
            : Label(label), IsLeaf(true), Type(type), X(0), Y(0), Scale(0.0f), TargetScale(1.0f) {
            
            // Set default shape and color based on node type
            switch (type) {
                case NodeType::Start: Shape = ShapeType::Capsule; R = 50; G = 200; B = 50; break;
                case NodeType::Action: Shape = ShapeType::Rectangle; R = 50; G = 100; B = 200; break;
                case NodeType::Condition: Shape = ShapeType::Diamond; R = 200; G = 150; B = 50; break;
                case NodeType::End: Shape = ShapeType::Capsule; R = 200; G = 50; B = 50; break;
                default: Shape = ShapeType::Rectangle; R = 100; G = 100; B = 100; break;
            }
        }

        /**
         * @brief Add a child node with an optional edge label
         * @param child Pointer to the child node (ownership transferred)
         * @param connectionLabel Label to display on the connecting edge
         */
        void AddChild(TreeNode* child, const std::string& connectionLabel = "") {
            Connections.push_back({ child, connectionLabel });
            IsLeaf = false;
        }

        /**
         * @brief Destructor - recursively deletes all child nodes
         * 
         * Ensures proper cleanup of the entire subtree.
         */
        ~TreeNode() {
            for (auto& conn : Connections) {
                delete conn.Target;
            }
        }
    };

}
