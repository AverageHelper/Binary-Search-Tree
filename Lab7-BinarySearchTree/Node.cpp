#include "Node.h"

Node::Node(int data) {
    this->data = data;
    left = nullptr;
    right = nullptr;
}

Node::~Node() {
    left = nullptr;
    right = nullptr;
}

/**
 * Returns the data that is stored in this node
 *
 * @return the data that is stored in this node.
 */
int Node::getData() const {
    return data;
}

/**
 * Returns the left child of this node or null if it doesn't have one.
 *
 * @return the left child of this node or null if it doesn't have one.
 */
NodeInterface* Node::getLeftChild() const {
    return left;
}

/**
 * Returns the right child of this node or null if it doesn't have one.
 *
 * @return the right child of this node or null if it doesn't have one.
 */
NodeInterface* Node::getRightChild() const {
    return right;
}

void Node::setLeftChild(NodeInterface* node) {
    this->left = node;
}

void Node::setRightChild(NodeInterface* node) {
    this->right = node;
}

bool Node::isLeaf() {
    return (getLeftChild() == nullptr) && (getRightChild() == nullptr);
}

Node* Node::largestSubnode() {
    NodeInterface* rightNode = getRightChild();
    NodeInterface* largestNode = nullptr;
    int largestValue = INT_MIN;
    
    if (rightNode == nullptr) {
        return this;
    }
    
    while (rightNode != nullptr) {
        if (largestValue < rightNode->getData()) {
            largestValue = rightNode->getData();
            largestNode = rightNode;
        }
        
        rightNode = rightNode->getRightChild();
    }
    
    return static_cast<Node*>(largestNode);
}
