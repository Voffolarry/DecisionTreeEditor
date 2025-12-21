#ifndef NODE_H
#define NODE_H

#include <string>

class Node {
    public:
       std::string question;
       std::string decision;
    public:
    // int data;
       Node* yes;
       Node* no;
      // Node* createNode(int data);
       bool isleaf;

       Node(const std::string& questionText);

       Node(const std::string& decisionText, bool leaf);
};
#endif