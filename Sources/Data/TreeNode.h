#pragma once

#include <string>
#include <vector>
#include <functional>
#include <cstdint>

namespace Data {

    enum class NodeType {
        Start,
        Action,
        Condition,
        End
    };

    enum class ShapeType {
        Circle,
        Rectangle,
        Diamond,
        Capsule
    };

    struct TreeNode; // Forward decl

    struct Connection {
        TreeNode* Target;
        std::string Label;
    };

    struct TreeNode {
        std::string Label;
        std::vector<Connection> Connections;
        bool IsLeaf; // Deprecated conceptually but kept for now? Maybe remove.
        NodeType Type;
        ShapeType Shape;
        
        // Visual Properties
        uint8_t R, G, B;

        // Layout properties
        float X, Y;
        
        // Animation
        float Scale;
        float TargetScale;

        TreeNode(const std::string& label, NodeType type = NodeType::Action) 
            : Label(label), IsLeaf(true), Type(type), X(0), Y(0), Scale(0.0f), TargetScale(1.0f) {
            
            // Set Default Shape and Color based on Type
            switch (type) {
                case NodeType::Start: Shape = ShapeType::Capsule; R = 50; G = 200; B = 50; break;
                case NodeType::Action: Shape = ShapeType::Rectangle; R = 50; G = 100; B = 200; break;
                case NodeType::Condition: Shape = ShapeType::Diamond; R = 200; G = 150; B = 50; break;
                case NodeType::End: Shape = ShapeType::Capsule; R = 200; G = 50; B = 50; break;
                default: Shape = ShapeType::Rectangle; R = 100; G = 100; B = 100; break;
            }
        }

        void AddChild(TreeNode* child, const std::string& connectionLabel = "") {
            Connections.push_back({ child, connectionLabel });
            IsLeaf = false;
        }

        ~TreeNode() {
            for (auto& conn : Connections) {
                delete conn.Target;
            }
        }
    };

}
