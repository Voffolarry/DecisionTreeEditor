#ifndef DECISIONTREE_H
#define DECISIONTREE_H

#include "Node.h"

class DecisionTree{
    public:
      DecisionTree();
    private:
      Node* mroot; /* Root or starting point of the decision tree */ 
    public:
      void BuildTree();
      Node* getRoot();
      Node* next(Node* current, bool);   /* Aller a gauche ou a droite */  
};

#endif
