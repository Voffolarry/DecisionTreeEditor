#include "DecisionTree.h"

DecisionTree::DecisionTree() : mroot(nullptr){}

/**
 * Construction de l'arbre
 */
 void DecisionTree::BuildTree(){
    mroot = new Node("Age > 20 ?");

    mroot->yes = new Node("Adult", true);
    mroot->no = new Node("Minor", true);
 }

 /**
  * Acceder a l'arbre
  */
 Node* DecisionTree::getRoot(){
    return mroot;
 }

 /**
  * Navigation dans l'arbre
  */
 Node* DecisionTree::next(Node* current, bool answer){
    if(current->isleaf){
        return current;
    }
    return answer ? current->yes : current->no;
}