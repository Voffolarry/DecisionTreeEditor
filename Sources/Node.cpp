#include "Node.h"


Node::Node(const std::string& questionText):
      question(questionText),
      decision(""),
      yes(nullptr),
      no(nullptr),
      isleaf(false){}




Node::Node(const std::string& decisionText, bool leaf):
      question(""),
      decision(decisionText),
      yes(nullptr),
      no(nullptr),
      isleaf(leaf){}      


















// Node* createNode(int data){
//     Node* newNode = new Node::Node(1);
//     newNode->data = data;
//     newNode->left = newNode->right = nullptr;
//     return newNode;
// }

