#ifndef Node_h
#define Node_h

#include <climits>
#include "NodeInterface.h"

class Node: public NodeInterface {
private:
    int data;
    NodeInterface* left;
    NodeInterface* right;
    
public:
    Node(int data);
    ~Node();
    
    /**
     * Returns the data that is stored in this node
     *
     * @return the data that is stored in this node.
     */
    int getData() const;
    
    /**
     * Returns the left child of this node or null if it doesn't have one.
     *
     * @return the left child of this node or null if it doesn't have one.
     */
    NodeInterface* getLeftChild() const;
    
    /**
     * Returns the right child of this node or null if it doesn't have one.
     *
     * @return the right child of this node or null if it doesn't have one.
     */
    NodeInterface* getRightChild() const;
    
    void setLeftChild(NodeInterface* node);
    void setRightChild(NodeInterface* node);
    bool isLeaf();
    Node* largestSubnode();

};

#endif /* Node_h */
